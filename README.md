# A cross-platform maker based on JavaScript #

A general-purpose command line maker based on JavaScript.

# Compiling #

** Linux **

```bash
mkdir bin
cd bin
cmake .. -DCMAKE_CXX_COMPILER=g++
make
```

# Cheatsheet #

**General**
```
Js.include("other.js");  // include a jsmake javascript
```

**Args**

```bash
jsmake.exe -a "-o myvalue"
```

```

if (Args.exists("-o")) {            // check if option -o exists
    var value = Args.get("-o");     // get the value of -o
}
```

**System**
```
System.env("CLASSPATH");            // return the value of the environment variable  
System.setEnv("CLASSPATH","./");    // set a new environment variable 
System.exit(0);                     // exit with code
```

**Platform**
```
Platform.isWindows()    // return true if running on windows platform  
Platform.isWindows64()  // return true if running on windows 64 bit platform
Platform.isLinux()      // return true if running on linux platform
Platform.isMacOS()      // return true if running on MacOS platform
Platform.isFreeBSD()    // return true if running on Android platform
Platform.isIOS()        // return true if running on IOS platform
```

**Logging**
```
Log.info("info log")        // info
Log.warn("warning log")     // warning
Log.error("error log")      // error
Log.bold("bold!")           // bold 
Log.red("red")              // red color (no \n) 
Log.grey("grey")            // grey color (no \n) 
Log.green("green")          // green color (no \n) 
Log.yellow("yellow")        // yellow color (no \n) 
Log.blue("blue")            // blue color (no \n) 
Log.magenta("magenta")      // magenta color (no \n) 
Log.cyan("cyan")            // cyan color (no \n) 
Log.white("white")          // white color (no \n) 
Log.onCyan("onCyan")        // foreground color on Cyan (no \n)
Log.onGrey("onGrey")        // foreground color on Grey (no \n)
Log.onBlue("onBlue")        // foreground color on Blue (no \n)
Log.onGreen("onGreen")      // foreground color on Green (no \n)
Log.onRed("onRed")          // foreground color on Red (no \n)
```

**Directory**
```
Directory.getCurrent();                 // get current directory
Directory.setCurrent("/test");          // set the current directory
Directory.exists("/test")               // return true if directory exists
Directory.exists("/test/myfile.txt")    // return true if file exists
Directory.make("test");                 // create a new directory "test"
Directory.remove("test");               // remove directory "test"
var content = Directory.readTextFile("file.txt");   // return the content of a file
```

**Path**
```
Path.getFilename("/home/file.txt");     // return "file.txt"
Path.getDirectory("/home/file.txt");    // return "/home/"
Path.getExtension("/home/file.txt");    // return "txt"
```

**Processor**
```
var res = Processor.run("whoami");      // execute a command
Processor.getOutput();                  // get last Processor.run() output
Processor.getError();                   // get last Processor.run() error
```

**Terminal**
```
var res = Terminal.prompt(">");     // return the input value after showing the prompt
Terminal.multiline(true);           // set multiline input
Terminal.printKeyCodes();           // print the keycodes
Terminal.clearScreen()              // clear the screen 
```

**HTTPClient**
```
HttpClient.download("http://www.google.com/", "D:/test.html");  // download a page
```