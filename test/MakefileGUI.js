/***************************************************
 *
 * JSMAKEFILE GUI Script Test
 *
 * Copyright (C) 2020 Victrix Games
 *
 ***************************************************/

Gui.init();

while(true) {
    Gui.newFrame();
    Gui.test();
    Gui.render();
}

Gui.shutdown();
