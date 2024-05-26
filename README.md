# EspioQuest
An adventure game set in the Scottish Highlands, where players must solve riddles and trivia questions to progress through the game.

For Windows, uncomment these lines in the espoQuest.pro file:

CONFIG(debug,debug|release): LIBS +=    -lsfml-graphics-d \
                                        -lsfml-window-d \
                                        -lsfml-system-d \
                                        -lsfml-audio-d

CONFIG(release,debug|release): LIBS +=  -lsfml-audio \
                                        -lsfml-system \
                                        -lsfml-network \
                                        -lsfml-graphics \
                                        -lsfml-window
                                        
For Linux, uncomment these lines in the espoQuest.pro file:

#INCLUDEPATH += /usr/include/SFML

#LIBS += -L/usr/lib/x86_64-linux-gnu \
       # -lsfml-graphics \
       # -lsfml-window \
        #-lsfml-system \
       # -lsfml-audio \
       # -lsfml-network
       
Ensure you have SFML installed in your PC, and refer to 'Screenshots and instructions.pdf' file to open the file correctly in your QT Creator IDE. Don't forget to change the paths in any line of code that loads pictures or sounds after downloading pictures and sounds from the 'pictures.zip' file
