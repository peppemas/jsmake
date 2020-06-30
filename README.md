# A cross platform project builder based on javascript #
This is our custom project builder used to compile the Victrix 3D engine and our games.

# Cheatsheet #

**General**
```
Js.include("other.js");  // include a jsmake javascript
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
```

**Processor**
```
var res = Processor.run("whoami");  
Processor.getOutput();
Processor.getError(); 
```
