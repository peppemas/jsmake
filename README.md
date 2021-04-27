# A cross platform maker based on javascript #

A general purpose maker based on javascript. Actually it is used internally to build our own 3D Engine.

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
Platform.isWindows()    // return true if it's a windows platform  
Platform.isWindows64()  // return true if it's a windows 64 bit platform
Platform.isLinux()      // return true if it's a linux platform
Platform.isMacOS()      // return true if it's a MacOS platform
Platform.isFreeBSD()    // return true if it's an Android platform
Platform.isIOS()        // return true if it's a IOS platform
```

**Logging**
```
Logger.info("info log");  
Logger.warn("warning log"); 
Logger.error("error log");
Logger.bold("bold!");
```

**Filesystem**
```
Directory.getCurrent();  // get current directory
Directory.setCurrent("/test"); // set the current directory
Directory.exists("/test") // return true if directory exists
Directory.exists("/test/myfile.txt") // return true if file exists
```

**Processor**
```
var res = Processor.run("whoami");  // execute a command
Processor.getOutput();  // get last Processor.run() output
Processor.getError();   // get last Processor.run() error
```
