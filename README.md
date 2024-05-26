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
