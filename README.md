# A cross platform maker based on javascript #

A general purpose maker based on javascript. Actually it is used internally to build my own 3D Engine.

# Cheatsheet #

**General**
```
Js.include("other.js");  // include a jsmake javascript
```

**Args**

jsmake.exe -a "-o myvalue"

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
Logger.info("info log");  
Logger.warn("warning log"); 
Logger.error("error log");
Logger.bold("bold!");
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
