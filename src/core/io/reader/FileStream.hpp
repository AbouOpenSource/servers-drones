//
// Created by Maanrifa Bacar Ali on 24/12/2019.
//

#ifndef DRONEPROJECT_FILESTREAM_HPP
#define DRONEPROJECT_FILESTREAM_HPP

#include <string>
#include "../../../util/TypeUtil.hpp"


class FileStream
{

public:

private:

    class ReaderInterface {

    public:

        typedef std::function<void(const unsigned int row, const unsigned int col, std::string value)> StreamCallback;

        explicit ReaderInterface(const FileStream *file_stream);

        void read(const StreamCallback& stream_callback, const TypeUtil::Callback& on_finish, const TypeUtil::ErrorCallback& error_callback = nullptr);

    private:

        const FileStream* file_stream_;

    };

    class WriterInterface {

    public:

        explicit WriterInterface(const FileStream *file_stream);

        void write(unsigned int row, unsigned int col, const std::string& value);

        void persist(const TypeUtil::ErrorCallback& error_callback = nullptr) const;

    private:

        const FileStream* file_stream_;

        std::vector<std::vector<std::string>> data_;

    };

public:

    struct ReadOption {
        const char* delimiter;
        const bool trim;
    };

    explicit FileStream(std::string file_path, ReadOption options = {";", true});

    ReaderInterface reader() const;

    WriterInterface writer() const;

private:

    void file_error(const TypeUtil::ErrorCallback &error_callback) const;

    std::string file_path_;

    ReadOption options_;

};


#endif //DRONEPROJECT_FILESTREAM_HPP
