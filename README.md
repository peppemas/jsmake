# A cross platform project builder based on javascript #
This is our custom project builder used to compile the Victrix 3D engine and our games. test

# Cheatsheet #

**General**
```
Js.include("other.js");  // include a jsmake javascript
```
**Args**

jsmake.exe -a "-o myvalue"

```
if (Args.exists("-o")) {    // check if option -o exists
    var value = Args.get("-o");  // get the value of -o
}
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
var res = Processor.run("whoami");  
Processor.getOutput();
Processor.getError(); 
```
