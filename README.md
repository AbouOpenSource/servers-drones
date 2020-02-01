<div>

<span class="c1"></span>

</div>

## <span class="c14">Servers and Drone Project</span>

<span class="c27">The context of the project is to place servers and drones on a field and make them communicate with each other.</span>

## <span class="c4">Getting Started</span>

<span class="c27">Follow these instructions to get a copy of the project running on your local machine for development and testing purposes.</span>

## <span class="c4">Prerequisites</span>

<span class="c1"></span>

 <span class="c5">**CLion**</span>

<span class="c12"></span>

<span class="c25 c39">Install CLion, the C++ dedicated IDE from JetBrains (free for student purpose) available at</span> <span class="c39 c49">[https://www.jetbrains.com/clion/download/](https://www.google.com/url?q=https://www.jetbrains.com/clion/download/%23section%3Dwindows&sa=D&ust=1580571561470000)</span><span class="c25 c39">and run it on Windows, macOS, and Linux (for setup on FreeBSD, refer to</span> <span class="c24 c39">[this instruction](https://www.google.com/url?q=https://intellij-support.jetbrains.com/hc/en-us/articles/206525024-How-to-start-CLion-on-FreeBSD-&sa=D&ust=1580571561470000)</span><span class="c11 c39">).</span>

<span class="c11 c39"></span>

<span class="c35 c14">**C++ Compiler (to run C++ 17)**</span>

<span class="c11">For C/C++ projects, CLion uses GCC/G++, Clang, or MSVC toolset.</span>

*   <span class="c11">For Windows</span>

<span class="c25">You can select between MinGW/ MinGW-w64 or Cygwin environment,</span> <span class="c24">[WSL](https://www.google.com/url?q=https://docs.microsoft.com/en-us/windows/wsl/install-win10&sa=D&ust=1580571561471000)</span><span class="c25">, or</span> <span class="c24">[Visual Studio](https://www.google.com/url?q=https://visualstudio.microsoft.com/&sa=D&ust=1580571561472000)</span><span class="c25">if you plan to use Microsoft Visual C++ compiler. For details, refer to</span> <span class="c24">[Quick Tutorial: Configure CLion on Windows](https://www.google.com/url?q=https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html&sa=D&ust=1580571561472000)</span><span class="c11">.</span>

*   <span class="c11">For MacOS</span>

<span class="c25">On macOS, the required tools might be already installed. If not, update</span> <span class="c23">command line developer tools</span><span class="c25">as described in</span> <span class="c24">[Configuring CLion on macOS](https://www.google.com/url?q=https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-macos.html%23reqtools&sa=D&ust=1580571561472000)</span><span class="c11">.</span>

*   <span class="c11">For Linux</span>

<span class="c25">Compilers and make might also be pre-installed. In case of Debian/Ubuntu, install e</span> <span class="c24">[build_essentials](https://www.google.com/url?q=https://packages.ubuntu.com/xenial/build-essential&sa=D&ust=1580571561473000)</span><span class="c25">package and, if required, the</span> <span class="c24">[llvm](https://www.google.com/url?q=http://apt.llvm.org/&sa=D&ust=1580571561473000)</span><span class="c25"> package to get Clang.</span>

<span class="c12"></span>

## <span class="c4">Deploying the project</span>

<span class="c1"></span>

<span class="c11 c39"></span>

<span class="c35 c14">**Cloning GitHub repository**</span>

<span class="c1"></span>

*   <span>Choose</span> <span class="c6">VCS | Get from Version Control</span>

<span>or</span> <span class="c14">Get From Version Control</span><span class="c1"> on the Welcome screen if no project is currently opened.</span>

<span class="c1"></span>

*   <span>Specify the</span><span class="c14"> URL</span><span class="c1"> of the remote repository in the dialog box (You will need to login to your GitHub Account).</span>

<span class="c1"></span>

*   <span>Click</span> <span class="c14">Clone.</span> <span>Click “Yes” in the confirmation dialog box. The project will be cloned.</span>

<span class="c1"></span>

<span class="c11 c39"></span>

<span class="c5">**Running the cloned project**</span>

<span class="c5"></span>

<span class="c1"></span>

<span class="c14">Build, Debug</span> <span>or</span> <span class="c14">Run</span> <span class="c1">the project using the tools on the top right corner of CLion Window.</span>

<span class="c1"></span>

<span class="c5"></span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 542.00px; height: 40.00px;">![](images/image4.png)</span>

<span class="c5"></span>

<span class="c5"></span>

<span class="c5"></span>

<span class="c5"></span>

<span class="c5"></span>

<span class="c5"></span>

<span class="c5"></span>

<span class="c5"></span>

<span class="c5"></span>

<span class="c5"></span>

<span class="c5"></span>

## <span class="c14">Architecture</span>

<a id="t.45ea6120553329215d7f8c4efe74e693f036bbba"></a><a id="t.0"></a>

<table class="c40">

<tbody>

<tr class="c21">

<td class="c41" colspan="1" rowspan="1">

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 118.99px; height: 445.50px;">![](images/image8.png)</span>

</td>

<td class="c41" colspan="1" rowspan="1">

<span class="c55">We use Model View Controller (MVC) as the main architecture for the project which</span> <span>allows the program to have a good scalability, works separation.</span>

<span class="c14">Model :</span> <span class="c1">it is the application's dynamic data structure, independent of the user interface.</span>

<span class="c14">Controller:</span> <span class="c1">controller acts on both model and view. It controls the data flow into model object and updates the view whenever data changes. It keeps the view and model separate.</span>

<span class="c14">View:</span> <span class="c1">represents the visualization of the data that model contains.</span>

<span class="c15"></span>

<span class="c15"></span>

<span class="c15"></span>

</td>

</tr>

</tbody>

</table>

<span class="c4"></span>

<span class="c45 c14">**Event-based programming**</span>

<span class="c1"></span>

<span class="c1">We also implemented an event-based programming which allow the controller to subscribe at some events and react to them.</span>

<span class="c5"></span>

<span class="c35 c14">**Example**</span>

<span class="c15"></span>

<span class="c1">We subscribe to an event called “FRAME_UPDATED” in the DirectionController, and when a publish on this event happen. The callback function passed to the subscribe function will be executed.</span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 624.00px; height: 82.67px;">![](images/image6.png)</span>

<span class="c1"></span>

<span>From the window when the onDraw() method is called, we publish the event “FRAME_UPDATED”.</span>

<span class="c1"></span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 343.50px; height: 151.38px;">![](images/image1.png)</span>

<span class="c15"></span>

<span class="c14 c45">**Main folders**</span>

<span class="c15"></span>

<a id="t.15c85f05e8d125c264972b9c59d06485e64db5f9"></a><a id="t.1"></a>

<table class="c40">

<tbody>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c6">**Folder name**</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c6">**Purpose**</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">data</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">It contains the image displayed on the window, server files and the constant data.</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">lib</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">It contains the glutInterface library to interact with the window and its associated events.</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">src</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">The most important folder, where the Model View Controller acts.</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">test</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">The tests to check if all is working. (we don’t really use it at the moment)</span>

</td>

</tr>

</tbody>

</table>

<span class="c15"></span>

## <span class="c4">Project organization</span>

<span class="c1"></span>

<a id="t.de21ad8ff47ff194012a54c16504d11deb18c475"></a><a id="t.2"></a>

<table class="c40">

<tbody>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c6">**Parts**</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c6">**Members**</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Geometry [convex hull, triangulation, Delaunay triangulation, mesh, Voronoï Diagram]</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Julien and Joshua</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Drone animation in accordance with the servers [initialization, position, acceleration, speed,  direction, inertia, force, velocity, collision detection, collision prevention]</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Abou and Maanrifa</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Code organisation, optimization, architecture implementation.</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Maanrifa</span>

</td>

</tr>

</tbody>

</table>

<span class="c1"></span>

<span class="c1">We fixed parts but we could still help each other on those parts. The  documentation, report, slideshow have been made by all of us.</span>

<span class="c1"></span>

## <span class="c4">Conventions</span>

<span class="c5">**File**</span>

<span class="c5"></span>

*   <span class="c1">.hpp, .cpp</span>
*   <span class="c1">.tcc, .cpp for template class</span>

<span class="c1"></span>

<span class="c1"></span>

<span class="c14 c35">**Code**</span>

<span class="c1"></span>

<a id="t.8180608cdc44bb5c57989ca108d34e7c8f509eed"></a><a id="t.3"></a>

<table class="c30">

<tbody>

<tr class="c21">

<td class="c37" colspan="1" rowspan="1">

<span class="c1"></span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">**Do**</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">**Don’t**</span>

</td>

</tr>

<tr class="c21">

<td class="c37" colspan="1" rowspan="1">

<span class="c1">Curly Brackets</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 237.50px; height: 78.79px;">![](images/image7.png)</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 237.00px; height: 79.00px;">![](images/image5.png)</span>

</td>

</tr>

<tr class="c21">

<td class="c37" colspan="1" rowspan="1">

<span class="c1">Class name</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">CamelCase</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">Others</span>

</td>

</tr>

<tr class="c21">

<td class="c37" colspan="1" rowspan="1">

<span class="c1">Method name</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">snake_case</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">Others</span>

</td>

</tr>

<tr class="c21">

<td class="c37" colspan="1" rowspan="1">

<span class="c1">Global variable name</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">snake_case</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">Others</span>

</td>

</tr>

<tr class="c21">

<td class="c37" colspan="1" rowspan="1">

<span class="c1">Class variable name</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">Snake_case with trailing underscore</span>

<span class="c1">Ex: “std::string drone_server_”</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">Others</span>

</td>

</tr>

<tr class="c21">

<td class="c37" colspan="1" rowspan="1">

<span class="c1">Constante</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">UPPER_CASE with underscore</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">Others</span>

</td>

</tr>

<tr class="c21">

<td class="c37" colspan="1" rowspan="1">

<span class="c1">Instantiation</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">int number(3)</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">int number = 3</span>

</td>

</tr>

<tr class="c21">

<td class="c37" colspan="1" rowspan="1">

<span class="c1">Array, vector preference</span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">std::array<type, size></span>

<span class="c1">or</span>

<span class="c1">std::vector<type></span>

</td>

<td class="c13" colspan="1" rowspan="1">

<span class="c1">new type[size]</span>

</td>

</tr>

</tbody>

</table>

<span class="c1"></span>

## <span class="c14">Project steps</span>

<span class="c1"></span>

<span class="c1"> The project was implemented by following the given steps systematically:</span>

<span class="c1"></span>

*   <span class="c1">Read server file.</span>
*   <span class="c1">Place all the servers on the field.</span>
*   <span class="c1">Draw convex hull using all the server points as well as the interior points (Graham scan algorithm).</span>
*   <span class="c1">Use triangulation to create triangles in the convex hull.</span>
*   <span class="c1">Apply delaunay to equilibrate the triangles.</span>
*   <span class="c1">Use Voronoi to find the area polygon</span>
*   <span class="c1">Use Heron’s method to calculate the surface area of polygon</span>
*   <span class="c1">Divide the drones across each area</span>

<span class="c5"></span>

## <span class="c4">Server File</span>

<span class="c5">**File Format**</span>

<span class="c5"></span>

<span class="c5"></span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 624.00px; height: 25.33px;">![](images/image2.png)</span>

<span class="c1"></span>

<span class="c35 c14">**Example**</span>

<span class="c1"></span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 624.00px; height: 98.67px;">![](images/image3.png)</span>

<span>        </span>

<span class="c35 c14">__Valid server colors__</span>

<span class="c6"></span>

<span>“RED”, “ORANGE”, “YELLOW”, “GREEN”, “CYAN”, “BLUE”, “PINK”, “PURPLE”, “MAGENTA”, “GREY”, “BROWN”           </span>

<span class="c1"></span>

## <span class="c4">Functionalities</span>

<span class="c35 c14">**Read Options**</span>

<span class="c1">        </span>

<a id="t.40b12907508d41e856644204710ddde4c50f2b5e"></a><a id="t.4"></a>

<table class="c31 c51">

<tbody>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c6">**Option**</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c6">**Action**</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">-h</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Print help text</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span>-</span><span>c filename</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Load file with specified filename</span>

</td>

</tr>

</tbody>

</table>

<span class="c1"> </span>

<span class="c5"></span>

<span class="c35 c14">**Event Handling**</span>

<span class="c1"></span>

<a id="t.2417a3b2a32fc37584ef615d2063614d210d22ab"></a><a id="t.5"></a>

<table class="c51 c31">

<tbody>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c6">**Event**</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c6">**Action**</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Left click on the server</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Select a server</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Click left outside</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Unselect all the servers</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Press Del key</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Delete the selected servers</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Press 1 to 9</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Change the color of selected servers</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Press 0</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Put a random color for the selected servers</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Right Click in the window</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Adding one server on the current position of the mouse</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Press “s” key</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Update the current configuration file with the new configuration (for example the new added server)</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Press “d” o “enter” key</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Adding the new drone from the coordinates (0,0)</span>

</td>

</tr>

<tr class="c21">

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Mouse right click on a drone</span>

</td>

<td class="c2" colspan="1" rowspan="1">

<span class="c1">Remove the drone</span>

</td>

</tr>

</tbody>

</table>

<span class="c1"></span>

<span class="c1"></span>

<span class="c1"></span>

## <span class="c4">Built With</span>

*   <span class="c27">C++ (Version 17)</span><span class="c28 c27"> - The programming language used</span>
*   <span class="c28 c27">CMake Version - 3.14</span>
*   <span class="c28 c27">CLion - The IDE used</span>

## <span class="c4">Versioning</span>

<span class="c28 c27">We use GitHub for versioning.</span>

## <span class="c4">Cloning</span>

<span class="c27">Clone the project repository to your local machine using</span> <span class="c19">[https://github.com/AbouOpenSource/servers-drones](https://www.google.com/url?q=https://github.com/AbouOpenSource/servers-drones&sa=D&ust=1580571561505000)</span>

## <span class="c14">Team</span>

*   <span class="c27 c28">Abou Sanou</span>
*   <span class="c28 c27">Joshua Shakya</span>
*   <span class="c28 c27">Julien Lecoq</span>
*   <span class="c27">Maanrifa Bacar Ali</span>

## <span class="c14">Contributing</span>

<span class="c27">Your contributions are always welcome!</span>

## <span class="c4">Acknowledgments</span>

*   <span class="c28 c27">Professor Benoit Piranda</span>
*   <span class="c28 c27">Professor Abdallah Makhoul</span>
