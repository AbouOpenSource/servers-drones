//
// Created by Maanrifa Bacar Ali on 24/12/2019.
//

#include <fstream>
#include <utility>
#include <vector>
#include "FileStream.hpp"
#include "../../../util/StringUtil.hpp"
#include "../../../util/VectorUtil.tcc"

FileStream::FileStream(std::string file_path, const FileStream::ReadOption options)
        : file_path_(std::move(file_path)), options_(options)
{}

void FileStream::file_error(const TypeUtil::ErrorCallback &error_callback) const
{
    std::string error = "Failed to open file " + file_path_;
    if (error_callback) {
        error_callback(error);
    } else {
        std::cout << error << std::endl;
        exit(errno);
    }
}

FileStream::ReaderInterface FileStream::reader() const
{
    return ReaderInterface(this);
}

FileStream::WriterInterface FileStream::writer() const
{
    return WriterInterface(this);
}

FileStream::ReaderInterface::ReaderInterface(const FileStream *file_stream): file_stream_(file_stream)
{}

void FileStream::ReaderInterface::read(const StreamCallback &stream_callback,
                                       const TypeUtil::Callback &on_finish,
                                       const TypeUtil::ErrorCallback &error_callback)
{
    std::ifstream file;
    file.open(file_stream_->file_path_);

    if  (!file) {
        file_stream_->file_error(error_callback);
        return;
    }

    unsigned int row(0), col(0);
    std::size_t current, previous = 0;
    std::string line;

    TypeUtil::Callback next = [this, &stream_callback, &line, &current, &previous, &row, &col] () {
        auto value = line.substr(previous, current - previous);
        stream_callback(row, col, file_stream_->options_.trim ? StringUtil::trim(value) : value);
    };

    while (std::getline( file, line ))
    {
        previous = 0;
        current = line.find(file_stream_->options_.delimiter);
        while (current != std::string::npos) {
            next();
            previous = current + 1;
            current = line.find(file_stream_->options_.delimiter, previous);
            col++;
        }
        next();
        col = 0;
        row++;
    }

    file.close();
    on_finish();
}

FileStream::WriterInterface::WriterInterface(const FileStream *file_stream)
    : file_stream_(file_stream), data_(std::vector<std::vector<std::string>>())
{}

void FileStream::WriterInterface::write(unsigned int row, unsigned int col, const std::string& value)
{
    VectorUtil::ensure_size(data_, row, [this] () {data_.emplace_back();});
    VectorUtil::ensure_size(data_[row], col, [this, &row] () {data_[row].emplace_back();});
    data_[row][col] = value;
}

void FileStream::WriterInterface::persist(const TypeUtil::ErrorCallback& error_callback) const
{
    std::ofstream file;
    file.open(file_stream_->file_path_);

    if  (!file) {
        file_stream_->file_error(error_callback);
        return;
    }

    unsigned long rows(data_.size()), cols;

    for (unsigned long i = 0; i < rows; ++i) {
        cols = data_[i].size();
        for (unsigned long j = 0; j < cols; ++j) {
            file << data_[i][j] << (j < cols - 1 ? file_stream_->options_.delimiter : "");
        }
        if (i < rows - 1) {
            file << std::endl;
        }
    }

    file.close();
}
