#include "questionbank.h"
#include <QDebug>

// Constructor for QuestionBank class
QuestionBank::QuestionBank() {}

// Getter method to retrieve the list of questions
QList<Question> QuestionBank::getQuestionList(){
    return questions;
}

// Method to load predefined questions into the question bank
QList<Question> QuestionBank::loadQuestion(){

    // Define and initialize sample questions
    Question q1("The Glenwatcher is a mythical creature said to possess the ability to forsee the future." , {"True", "False"}, "The Glenwatcher is a mythical figure in local folklore.", 1, "True/False");

    Question q2 ("In the misty glens of Glenhaven, ancient stones bear mysterious markings. The villagers \nwhisper that these stones hold secrets of the Emerald Cipher. Decipher the message:\n`GUR PENML XRL VF ZL FRPERG CBFG`\nWhat does the message reveal?",
                {"THE EMERALD KEY IS MY SECRET PATH", "THE RIDDLE KEY IS MY SECRET CODE", "THE EMERALD KEY IS MY SECRET WORD", "THE HIDDEN GEM IS MY FORBIDDEN QUEST"},
                "The stones were discovered by a local shepherd, who claimed to have heard whispers in the wind when standing near them.", 1, "MCQ");

    Question q3 ("Angus MacLeod, the village elder, has given you a cryptic message:\n'4 15 22 5 18 20 1 20 8 15 14 5'\nHe hints that it's a simple cipher, but the key lies in their family crest.\n What does the message reveal?",
                {"DOVE RETREAT AT THORN LANE", "FOREVER TALK AT HOTEL PHONE", "DOVE RETREAT AT HOTEL SHINE", "FOREVER TALK AT THORN GLEN"},
                "The MacLeod family crest features a bull's head with a crescent moon above it. The crescent moon has 13 points.", 2, "MCQ");

    Question q4("Legend has it that beneath the ancient ruins of Dunhaven Castle lies the key to unlocking unimaginable power—a relic known as the Emerald Cipher.", {"True", "False"}, "Local legends speak of the power hidden within the depths of Dunhaven Castle.", 0, "True/False");

    Question q5("An old villager remembers a forgotten lullaby, passed down through generations:\n'In the land of the Scots, where the thistle blooms\nSeek the key in the silence of the rooms\nWhere shadows dance, and the wind whispers low\nFind the answer, and the cipher will glow'\nWhat does the lullaby hint at?",
                {"THE EMERALD ROOM HOLDS THE CLUE", "THE SILENT TOMB GUARDS THE PRIZE", "THE HIDDEN ROOM HIDES THE TRUTH", "THE QUIET HOUSE HOLDS THE CIPHER"},
                "The villager remembers singing this lullaby to her children, but the meaning was lost over time.", 3, "MCQ");

    Question q6("You've discovered an ancient blueprint of Dunhaven Castle, with strange symbols \nand markings. One section reads:\n'3-14-15 1-18-5 20-8-5-19 1-20-20'\nWhat does this section reveal about the castle's layout?",
                {"CHAPEL AREA THE STATE TAT", "NOVA REEF TESTE THAT TASTE", "CHAPEL AREA THES STONE ATT", "NOVA RIFT THES STATE THAT"},
                "The blueprint was hidden in a secret compartment, guarded by a mysterious symbol etched into the wall.", 3, "MCQ");

    Question q7("In the village square, an ancient pedestal holds a riddle:\n'I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?'\nWhat is the answer to the riddle?",
                {"FIRE", "WATER", "WIND", "EARTH"},
                "The pedestal is engraved with symbols representing the elements of nature.", 2, "MCQ");

    Question q8("As dusk settles over the mist-shrouded village of Glenhaven,\n as weary traveler, you stumble upon a weathered parchment hidden among the ancient stones near Dunhaven Castle.\n The parchment bears a cryptic message:\n'JRW EB XLI UYIIV MR XLI WSEPPIV'. Intrigued by its mysterious aura, you endeavor to decipher the message, hoping it holds the key to unlocking the secrets of Glenhaven.\n What does the message reveal?",
                {"THE KEY TO THE PUZZLE IS THE HINT", "YOU ARE THE WINNER OF THE GAME", "THE END IS NEAR, KEEP SOLVING", "FIND ME IN THE HIDDEN CHAMBER"},
                "The traveler recalls tales of hidden chambers within Dunhaven Castle, rumored to contain ancient artifacts and treasures.", 0, "MCQ");

    Question q9("According to local lore, Glenhaven is shrouded in misty glens and whispered secrets,\n where ancient stones bear mysterious markings. What do villagers believe these stones hold?",
                {"Clues to the Emerald Cipher", "Messages from the spirits", "Directions to hidden treasures", "Recipes for ancient potions"},
                "Legend has it that these stones hold secrets of the Emerald Cipher, the key to unimaginable power.", 0, "MCQ");

    Question q10("During a recent excavation near Dunhaven Castle, archaeologists uncovered a weathered parchment with a cryptic message:\n'THE GUARDIAN OF THE KEY SLEEPS BENEATH THE SILVER MOON.'\n What might this message refer to?",
                 {"A statue in the village square", "An ancient tree in the forest", "A hidden chamber in the castle", "A cave by the nearby river"},
                 "The parchment was found buried near the castle's entrance, sparking rumors among the villagers.", 2, "MCQ");

    Question q11("In the heart of the Enchanted Forest lies a hidden glade where the whispers of ancient trees tell tales of the Moonlight Guardian.",
                 {"True", "False"}, "Legends speak of a mysterious guardian protecting the secrets of the forest.", 0, "True/False");

    Question q12 ("You stumble upon a secluded bar nestled in the heart of Glenhaven.\nThe bartender, an elderly man with a weathered face, beckons you over with a nod.\nHe slides a tattered map across the counter towards you, whispering,\n'The key lies...'",
                 {"MOON'S WATCHFUL EYE", "GLOWING EMERALD", "WHISPERING FOREST", "EARTHEN CLIFF"},
                 "The bartender nods towards a painting of a crescent moon\nhanging above the fireplace.",
                 0,
                 "MCQ");

    Question q13 ("You enter a dimly lit library filled with ancient tomes and dusty scrolls.\nAs you browse the shelves, a frail librarian approaches,\noffering an old book with worn pages. 'The secrets lie within...',\nshe whispers.",
                 {"HIDDEN CHAMBER PATH", "ANCIENT GUARDIAN'S LEGACY", "EMERALD'S MOONLIGHT REFLECTION", "SECRET GATE WORD"},
                 "A faded illustration depicts a bull's head with a crescent moon\nemblazoned above it.",
                 2,
                 "MCQ");

    Question q14 ("In the center of the village square stands an ornate fountain, its waters glistening in the sunlight.\nCarvings adorn the base of the fountain, and as you approach, you notice a riddle engraved in stone:\n'I flow without a source, yet never run dry...'",
                 {"FLOW WITHOUT SOURCE", "QUIVER IN BREEZE", "SPEAK WITHOUT VOICE", "DANCE WITH MOONLIGHT"},
                 "Carvings around the fountain depict symbols representing the elements of nature.",
                 0,
                 "MCQ");

    Question q15 ("Venturing deeper into the Enchanted Forest, you encounter a figure cloaked in mist.\nThe figure beckons you closer, whispering words lost to time.\n'The guardian awaits...', it murmurs softly.",
                 {"SACRED GROVE PATH", "ANCIENT SPIRITS", "VILLAGE CURSE", "EMERALD'S CASTLE REFUGE"},
                 "Wisps of mist swirl around the figure, forming patterns reminiscent of ancient symbols.",
                 1,
                 "MCQ");

    Question q16 ("Lost in the depths of the forest, you stumble upon an ancient stone altar adorned with enigmatic symbols.\nA whispering breeze seems to echo through the trees, revealing a riddle etched into the stone:\n'I can be cracked, made, and told,\nbut never seen. What am I?'",
                 {"A JOKE", "A SECRET", "A STORY", "A CODE"},
                 "The symbols on the altar depict scenes from ancient legends.",
                 0,
                 "MCQ");

    Question q17 ("As you explore the village's hidden corners, you come across a weathered tome resting on a dusty shelf.\nOpening it reveals a riddle inscribed on the first page:\n'The more you take, the more you leave behind. What am I?'",
                 {"FOOTSTEPS", "MEMORY", "RIVER", "ROAD"},
                 "The tome is filled with forgotten tales of Glenhaven's past.",
                 0,
                 "MCQ");

    Question q18("Beneath the watchful gaze of the moon, an enigmatic statue stands in the village square, bearing a riddle:\n'I dance in the darkness, yet crave the light\nI wane and wax, in the depths of night\nWhat am I?'\nWhat is the answer to the riddle?",
                 {"FIRE", "WATER", "MOON", "STAR"}, "The statue is adorned with symbols depicting celestial bodies and phases of the moon.", 2, "MCQ");

    Question q19 ("Near the village inn, you notice an intricately carved wooden signpost.\nUpon closer inspection, you decipher a riddle engraved upon it:\n'I am not alive, but I grow;\nI don't have lungs, but I need air;\nI don't have a mouth, but water kills me.\nWhat am I?'",
                 {"FIRE", "TREE", "STONE", "SUN"},
                 "The signpost features carvings depicting scenes from Glenhaven's history.",
                 1,
                 "MCQ");

    Question q20 ("Within a hidden alcove, you discover a crumbling statue covered in ivy.\nAt its base lies a scroll bearing a mysterious inscription:\n'To find the key, seek the heart of the forest.\nBeneath the watchful eyes of the ancients, the truth awaits.'",
                 {"SACRED TREE GROVE", "ANCIENT RUINS", "FOREST'S HEART", "EMERALD'S GAZE"},
                 "The scroll hints at a location imbued with ancient magic and wisdom.",
                 0,
                 "MCQ");

    Question q21 ("At the edge of a moonlit clearing, you encounter a spectral figure shrouded in mist.\nIt beckons you closer and utters a cryptic riddle:\n'I am taken from a mine and shut up in a wooden case,\nfrom which I am never released, and yet I am used by almost every person.\nWhat am I?'",
                 {"GOLD", "SILVER", "IRON", "KNOWLEDGE"},
                 "The figure's form flickers, revealing glimpses of ancient symbols.",
                 3,
                 "MCQ");

    Question q22 ("In the village square, an old bard sings a haunting melody, weaving tales of ancient heroes and lost treasures.\nAfter the performance, he approaches you with a curious smile and hands you a parchment with a cryptic message:\n'P Y J K P Y J S'. Can you decipher its meaning?",
                 {"MYSTERY SOLVED", "SECRET UNCOVERED", "TREASURE HIDDEN", "PUZZLE PIECES"},
                 "The bard hints that the solution may lie in the rhythm of his songs.",
                 3,
                 "MCQ");

    Question q23 ("While exploring the abandoned mines near Glenhaven, you stumble upon a forgotten chamber with strange markings covering the walls.\nAmidst the ancient glyphs, you find a coded message carved into the stone:\n'V nz gur erfg bs gur bssvpre'. What does it say?",
                 {"I AM THE REST OF THE OFFICER", "I AM THE SURE OF THE BOSS", "I AM THE REASON OF THE BARD", "I AM THE REST OF THE BROTHER"},
                 "Legends say this chamber was once used by miners to hide their discoveries from raiders.",
                 0,
                 "MCQ");

    Question q24 ("In the dim light of the village tavern, an old sailor recounts tales of his voyages across stormy seas and distant lands.\nMoved by your curiosity, he slides a worn parchment across the table, bearing a mysterious inscription:\n'Zl jvsr vf n ybg tbbqre guna zl bja'. What does it mean?",
                 {"WIFE COOK BETTER", "SISTER SINGER GOOD", "DOG SWIMMER BEST", "SON COOK GOOD"},
                 "The sailor hints that the answer lies in his fond memories of home.",
                 0,
                 "MCQ");

    Question q25 ("A traveler encounters a fork in the road, with two paths leading into the unknown. One path is guarded by a fearsome dragon, while the other is shrouded in darkness. The traveler must choose wisely to continue their journey safely.",
                 {"True", "False"},
                 "The traveler's decision will determine their fate on the journey ahead.",
                 0,
                 "True/False");

    Question q26 ("While exploring the depths of Dunhaven Castle, you encounter a mysterious door with three glowing gems: ruby, sapphire, and emerald. An inscription reads:\n'Only the gem that mirrors the heart may enter.'\nThe emerald symbolizes harmony.",
                 {"True", "False"},
                 "Reflect on the symbolic meaning of the heart and which gem shares a similar meaning.",
                 0,
                 "True/False");

    Question q27 ("In the heart of the Enchanted Forest, a magical fountain offers travelers a choice between two enchanted goblets: one filled with sparkling water and the other with shimmering wine. A sign nearby reads:\n'Choose wisely, for one sip grants clarity, while the other clouds the mind.'\nThe goblet with water represents clarity.",
                 {"True", "False"},
                 "Consider the symbolic significance of water and its association with clarity.",
                 0,
                 "True/False");

    Question q28 ("Deep within the caverns of Glenhaven, you stumble upon a cryptic mural adorned with ancient symbols. A riddle inscribed below challenges your wit:\n'I am taken from a mine, and shut up in a wooden case, from which I am never released, and yet I am used by almost every person. What am I?'",
                 {"Gold", "Silver", "Coal", "Diamond"},
                 "Consider the properties of each material and their common uses.",
                 2,
                 "MCQ");

    Question q29 ("While exploring the ruins of Dunhaven Castle, you discover a hidden chamber with a mysterious locked chest. Engraved on the chest is a riddle:\n'What has keys but can't open locks, and rooms but can't hold objects?'",
                 {"A keyboard", "A map", "A tree", "A book"},
                 "Consider the symbolic meanings of keys and rooms.",
                 1,
                 "MCQ");

    Question q30 ("As you navigate the misty paths of Glenhaven, you encounter a weathered signpost with a cryptic message:\n'I am always hungry, I must always be fed. The finger I touch will soon turn red. What am I?'",
                 {"Flame", "Sun", "Time", "River"},
                 "Reflect on the symbolism and characteristics associated with each option.",
                 2,
                 "MCQ");

    Question q31 ("In the heart of the Enchanted Forest lies a hidden glade where the whispers of ancient trees tell tales of the Moonlight Guardian.",
                 {"True", "False"},
                 "Legends speak of a mysterious guardian protecting the secrets of the forest.",
                 0,
                 "True/False");

    Question q32 ("High atop the cliffs overlooking Glenhaven, a forgotten monument bears a cryptic inscription:\n'I am not alive, but I grow; I don't have lungs, but I need air; I don't have a mouth, but water kills me. What am I?'",
                 {"Tree", "Rock", "Fire", "Cloud"},
                 "Consider the characteristics of each option and their relationship to growth and sustenance.",
                 0,
                 "MCQ");

    Question q33 ("Within the hidden chambers of Dunhaven Castle, you uncover a series of intricate puzzles. One puzzle presents a grid of symbols and a cryptic clue:\n'Arrange the symbols in the correct order to unlock the secret passage. The clue lies in the stars.'",
                 {"True", "False"},
                 "Consider the significance of the stars and their relation to navigation and guidance.",
                 0,
                 "True/False");

    Question q34("In the depths of Glenhaven's enchanted forest, you discover an ancient altar with three crystals: amethyst, rose quartz, and citrine. A cryptic note reads:\n'Choose wisely, for only one crystal can bestow the blessing of insight.'\nAmethyst is linked to wisdom, rose quartz to love, and citrine to success.", {"Amethyst", "Rose Quartz", "Citrine"},
                 "Reflect on which crystal's property aligns most with the concept of insight.", 0, "MCQ");

    Question q35 ("As you journey through the enchanted forests of Glenhaven, you encounter a mystical creature known as the Forest Guardian. It poses a riddle:\n'This thing all things devours:\nBirds, beasts, trees, flowers;\nGnaws iron, bites steel;\nGrinds hard stones to meal;\nSlays king, ruins town,\nAnd beats mountain down.'",
                 {"Time", "Dragon", "Ogre", "Giant"},
                 "Consider the riddle's clues and the concept of time as a devourer of all things.",
                 0,
                 "MCQ");

    Question q36 ("Hidden within the labyrinthine catacombs of Dunhaven Castle, a riddle carved into the stone wall challenges your intellect:\n'The more you take, the more you leave behind. What am I?'",
                 {"Footsteps", "Memories", "Time", "Breath"},
                 "Contemplate the nature of each option and its relationship to leaving something behind.",
                 0,
                 "MCQ");

    Question q37 ("Deep within the caverns of Glenhaven, you discover an ancient tome guarded by a mystical seal. A riddle engraved upon the seal presents a challenge:\n'I am a word of letters three, add two and fewer there will be. What am I?'",
                 {"Few", "Several", "Couple", "Word"},
                 "Consider the nature of words and their transformation when letters are added or subtracted.",
                 2,
                 "MCQ");

    Question q38("Deep within the catacombs beneath Dunhaven Castle, you find a series of ancient runes etched into the walls. A riddle is written in the ancient language:\n'What has keys but can't open locks, and rooms but can't hold objects?'",
                 {"A keyboard", "A map", "A tree", "A book"},
                 "Consider the symbolic meanings of keys and rooms.",
                 1,
                 "MCQ");

    Question q39("In the heart of Glenhaven's town square, an old fountain holds a puzzling inscription:\n'I'm not alive, but I can grow; I don't have lungs, but I need air; I don't have a mouth, but water kills me. What am I?'",
                 {"A plant", "A fire", "A cloud", "A rock"},
                 "The inscription is surrounded by carved images of nature.",
                 0,
                 "MCQ");

    Question q40("While exploring the ruins of Dunhaven Castle, you discover a hidden chamber with a mysterious locked chest. Engraved on the chest is a riddle:\n'What has keys but can't open locks, and rooms but can't hold objects?'",
                 {"A keyboard", "A map", "A tree", "A book"},
                 "Consider the symbolic meanings of keys and rooms.",
                 1,
                 "MCQ");

    Question q41("As you wander through the Enchanted Forest, you come across an ancient stone with a riddle carved into its surface:\n'The more you take, the more you leave behind. What am I?'",
                 {"Footsteps", "Memory", "Time", "Breath"},
                 "The stone is surrounded by lush vegetation and mystical symbols.",
                 2,
                 "MCQ");

    Question q42("In the village tavern, a weathered traveler tells you of a mysterious riddle he once encountered on his travels:\n'Forward I am heavy, but backward I am not. What am I?'",
                 {"A ton", "A kilogram", "A pound", "A gram"},
                 "The traveler recalls seeing the riddle inscribed on an old stone tablet.",
                 3,
                 "MCQ");

    Question q43("While exploring the ancient ruins of Dunhaven Castle, you stumble upon a hidden chamber with a peculiar inscription:\n'What belongs to you, but others use it more than you do?'",
                 {"Your name", "Your house", "Your time", "Your money"},
                 "The chamber is adorned with intricate carvings depicting everyday life.",
                 0,
                 "MCQ");

    Question q44("In the heart of the Enchanted Forest, you encounter a magical creature guarding a treasure chest. It challenges you with a riddle:\n'I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?'",
                 {"Fire", "Water", "Wind", "Earth"},
                 "The creature's lair is adorned with sparkling crystals and shimmering lights.",
                 2,
                 "MCQ");

    Question q45("Within the depths of Dunhaven Castle, you uncover a hidden chamber containing an ancient scroll. Upon unrolling the scroll, you find a cryptic riddle:\n'I am taken from a mine, and shut up in a wooden case, from which I am never released, and yet I am used by almost every person. What am I?'",
                 {"Gold", "Silver", "Coal", "Diamond"},
                 "Consider the practical uses of each material.",
                 2,
                 "MCQ");

    Question q46("Deep within the Enchanted Forest, you encounter a mysterious stone with a riddle engraved upon it:\n'I'm not alive, but I can grow; I don't have lungs, but I need air; I don't have a mouth, but water kills me. I can be your guide, but only in darkness.'",
                 {"Moonlight", "A lantern", "A torch", "A star"},
                 "The stone is surrounded by lush greenery and vibrant flowers.",
                 0,
                 "MCQ");

    Question q47 ("In the depths of the village well, you discover an enchanted scroll with a cryptic message:\n'Three crowns guard the hidden trove: one of gold, one of silver, and one of bronze. Only the crown of bronze can open the way.'\nThe bronze crown holds the power to access the trove.", {"True", "False"}, "Consider the significance of the bronze crown and its unique role in accessing the hidden trove.", 0, "True/False");

    Question q48 ("Under the cover of darkness, you witness a gathering of four enigmatic figures: the Keeper of Shadows, the Seeker of Light, the Whisperer of Secrets, and the Guardian of Truth. According to local lore, only the Guardian of Truth holds the key to deciphering ancient texts.", {"True", "False"}, "The Guardian of Truth possesses the knowledge needed to understand the wisdom within ancient texts.", 0, "True/False");

    Question q49 ("A mysterious vendor offers three potions: the Potion of Vigor, the Potion of Clarity, and the Potion of Transformation. The Potion of Clarity can provide the insight needed to navigate the hidden dangers of the enchanted forest.", {"True", "False"}, "The Potion of Clarity is specifically designed to grant the knowledge required to overcome the forest's challenges.", 0, "True/False");

    Question q50 ("As you traverse the winding tunnels beneath Glenhaven Forest, you encounter a riddle etched into the cavern wall:\n'I am a path unseen, hidden in the depths; choose wisely between earth, fire, and sky. The sky path leads to the hidden temple.'", {"True", "False"}, "Consider the unique characteristics of each element and which aligns most closely with the hidden temple's location.", 0, "True/False");

    Question q51 ("At the crossroads of Glenhaven Forest, you find an old map with a cryptic note:\n'North, south, east, or west; where secrets hide, riches rest.'\nThe correct path is west.", {"True", "False"}, "Consider the message in the note and its relation to the correct path on the map.", 0, "True/False");

    Question q52 ("You discover three ancient tomes: the Book of Elements, the Book of Illusions, and the Book of Prophecies. A cryptic note hints that one book holds the key to the hidden treasure's location.\nThe Book of Elements contains the key to finding the treasure.", {"True", "False"}, "The Book of Elements holds vital information regarding the location of the treasure.", 0, "True/False");

    Question q53 ("As night falls over Dunhaven Castle, three spirits appear: the Spirit of Vengeance, the Spirit of Compassion, and the Spirit of Wisdom. Only the Spirit of Wisdom holds the knowledge to unlock the hidden chamber.", {"True", "False"}, "Consider which spirit's attribute is most relevant to unlocking the hidden chamber.", 0, "True/False");

    Question q54 ("Within the village library, you discover a coded message:\n'Yzft xnzpe fqr gfkmsviim vznfxy xzeugqe.'\nDecrypting it will reveal a clue about the Emerald Cipher.", {"True", "False"}, "The message contains a cipher that must be decoded to unveil a hint about the Emerald Cipher.", 0, "True/False");

    Question q55 ("In the depths of the Enchanted Forest, you encounter three magical runes: Lorus, Arcanum, and Mystrus. According to local lore, invoking the rune Mystrus will reveal the hidden cache of gemstones.", {"True", "False"}, "Mystrus is the rune with the power to uncover the hidden cache.", 0, "True/False");

    Question q56 ("During your quest, you come across a mysterious riddle:\n'I walk on four legs in the morning, two legs at noon, and three legs in the evening. What am I?'", {"A man", "A dog", "A horse", "A bird"}, "The riddle describes stages of life represented by different animals.", 3, "MCQ");

    Question q57 ("At the entrance of the hidden catacombs beneath Dunhaven, you find an encrypted message:\n'Sbhe unccraf qevax hc gur cbfref pnffyr.'\nDeciphering the message will reveal the catacombs' hidden danger.", {"True", "False"}, "The encrypted message warns about a hidden danger within the catacombs.", 0, "True/False");

    Question q58 ("Within the village library, you find a mysterious tome with a riddle inscribed:\n'I have a bed but never sleep; can run but never walk; can have a mouth but never talk. What am I?'", {"A river", "A tree", "A cloud", "A mountain"}, "Ponder the characteristics of natural elements and which one aligns with the riddle.", 0, "MCQ");

    Question q59 ("A wise sage presents you with three crystals: Moonstone, Sunstone, and Eclipse Stone. The sage claims that the Eclipse Stone can manipulate time and space.", {"True", "False"}, "The Eclipse Stone possesses the unique ability to control the fabric of time and space.", 0, "True/False");

    Question q60 ("Within the depths of Glenhaven Forest, a stone tablet reads:\n'One ring to reveal, one ring to conceal, and one ring to guide the way.'\nThe ring that reveals is the key to navigating the forest.", {"True", "False"}, "The ring that reveals holds the power to unveil the correct path through the forest.", 0, "True/False");

    Question q61 ("While exploring the depths of Glenhaven Forest, you come across three glowing orbs: blue, green, and red. A cryptic message hints that the green orb can grant the ability to communicate with animals.", {"True", "False"}, "Consider which orb's property aligns with the ability to communicate with animals.", 0, "True/False");

    Question q62 ("Within a hidden chamber of Dunhaven Castle, you discover a coded message:\n'Bz pbairef unf cvffyngr gb nqq rvtug bar.'\nDeciphering the code will reveal a crucial clue about the Emerald Cipher.", {"Add one to eight", "Subtract one from eight", "Multiply eight by two", "Divide eight by two"}, "Analyze the encoded message and its potential meanings related to the Emerald Cipher.", 2, "MCQ");

    Question q63 ("At the entrance of the Labyrinth of Illusions, you find a mysterious riddle:\n'I am an odd number; take away a letter, and I become even. What number am I?'", {"Five", "Seven", "Nine", "Eleven"}, "Analyze the characteristics of odd numbers and the effect of removing a letter from their names.", 2, "MCQ");

    Question q64 ("A cryptic note found within the village chapel reads:\n'Seek the moon's embrace when shadows dance; there, the hidden chamber shall be found.'\nThe hidden chamber can only be accessed during a full moon.", {"True", "False"}, "Consider the significance of the full moon and its relation to accessing the hidden chamber.", 0, "True/False");

    Question q65 ("Three elemental crystals lie before you: Ignis, Aquos, and Aeros. Ancient texts claim that Aquos holds the key to unlocking the secrets of the underwater city.", {"True", "False"}, "Aquos is the crystal associated with the power to reveal the underwater city's mysteries.", 0, "True/False");

    Question q66 ("Within the depths of the Enchanted Forest, you encounter a riddle:\n'I speak without a mouth, and hear without ears. I have no body, but I come alive with the wind. What am I?'", {"An echo", "A shadow", "A reflection", "A cloud"}, "Contemplate the natural phenomena that fit the description in the riddle.", 0, "MCQ");

    Question q67 ("In the heart of Glenhaven Forest, you find a mysterious note:\n'Two bodies have I, though both joined in one. The more still I stand, the quicker I run. What am I?'", {"An egg timer", "A sundial", "A hourglass", "A pendulum"}, "Reflect on the objects that may fit the description in the note.", 2, "MCQ");

    Question q68 ("A coded message within the village library reads:\n'Mhj nopx fmfxo gzrm glmt vx ujksg gur thmznx neju.'\nDecrypting the message will unveil the path to the hidden archive.", {"True", "False"}, "The encrypted message holds the key to locating the hidden archive.", 0, "True/False");

    Question q69 ("While exploring the hidden catacombs beneath Dunhaven, you come across a riddle:\n'I am a box without hinges, key or lid; yet golden treasure inside is hid - what am I?'", {"A treasure chest", "An egg", "A cave", "A book"}, "Consider the objects that can metaphorically fit the description in the riddle.", 1, "MCQ");

    Question q70 ("A wise sage speaks of three ancient relics: the Amulet of Perception, the Talisman of Truth, and the Bracelet of Wisdom. The sage claims that the Bracelet of Wisdom grants unparalleled insight.", {"True", "False"}, "The Bracelet of Wisdom is believed to bestow unparalleled insight upon its wearer.", 0, "True/False");

    Question q71 ("In the depths of Glenhaven Forest, you discover three enchanted feathers: blue, green, and red. An ancient legend claims that the red feather can bestow the gift of flight.", {"True", "False"}, "Consider which feather's property aligns with the ability to fly.", 0, "True/False");

    Question q72 ("A cryptic note found in the village library reads:\n'Where the shadow touches the moon's embrace, seek the entrance to the forgotten maze.'\nThe entrance to the forgotten maze is marked by a crescent moon symbol.", {"True", "False"}, "Reflect on the significance of the crescent moon symbol and its connection to the forgotten maze.", 0, "True/False");

    Question q73 ("While exploring the Labyrinth of Illusions, you come across a riddle:\n'I can be cracked, made, told, and played. What am I?'", {"A code", "A joke", "A story", "A game"}, "Examine the multiple meanings of the words 'cracked,' 'made,' 'told,' and 'played.'", 2, "MCQ");

    Question q74 ("A mysterious stone discovered within the Enchanted Forest bears a coded message:\n'Qgtrgl gtcfvg tgragcvg rtraqf.'\nDeciphering the code will reveal the secret to harnessing elemental powers.", {"True", "False"}, "The coded message provides crucial information about controlling elemental forces.", 0, "True/False");

    Question q75 ("Within the depths of the hidden catacombs, you find a riddle:\n'I can fill a room but take up no space. What am I?'", {"Light", "Sound", "Air", "Time"}, "Contemplate the various phenomena that can fill a space without occupying it.", 0, "MCQ");

    Question q76 ("Three magical tomes lie before you: the Tome of Time, the Tome of Space, and the Tome of Reality. Ancient texts claim that the Tome of Time holds the key to understanding the fabric of the universe.", {"True", "False"}, "The Tome of Time is believed to contain knowledge about the nature and workings of the universe.", 0, "True/False");

    Question q77 ("A wise sage speaks of three powerful gems: the Ruby of Courage, the Sapphire of Truth, and the Topaz of Illusion. The sage claims that the Sapphire of Truth can reveal hidden intentions.", {"True", "False"}, "The Sapphire of Truth is associated with the ability to discern hidden motives and intentions.", 0, "True/False");

    Question q78 ("During your exploration of Dunhaven Castle, you find a riddle:\n'I can be stolen, lacked, or kept; often wasted or even well-spent. What am I?'", {"Money", "Trust", "Time", "Love"}, "Analyze the multiple ways in which the words 'stolen,' 'lacked,' 'kept,' 'wasted,' and 'well-spent' can be applied.", 2, "MCQ");

    Question q79 ("Within the depths of Glenhaven Forest, a mysterious note reads:\n'The song of the wind, the dance of the leaves; where nature's rhythm comes alive, the Hidden Glade deceives.'\nThe Hidden Glade is concealed amidst the living, breathing heart of the forest.", {"True", "False"}, "Consider the relationship between the Hidden Glade and the living, breathing forest described in the note.", 0, "True/False");

    Question q80 ("A coded message found within the village chapel reads:\n'Qwemjgy bcla ibevk slafqe mcfw ab mrglq tcetx gji tgebhsb.'\nDeciphering the code will reveal the way to access the Celestial Archives.", {"True", "False"}, "The coded message holds the key to unlocking the Celestial Archives.", 0, "True/False");

    Question q81("The Guardian of Light is rumored to manifest in the form of a radiant phoenix, soaring high above the Stormy Coast.",
                 {"True", "False"}, "Whispers among sailors suggest that the Guardian of Light appears in the form of a radiant phoenix, guiding ships through stormy waters.", 0, "True/False");

    Question q82("According to legend, the Guardian of Frost is said to command the icy winds and freezing temperatures of the Frozen Wastes.",
                 {"True", "False"}, "Local lore speaks of the Guardian of Frost as a mystical being who wields control over scorching heat.", 1, "True/False");

    Question q83("Whispers among the villagers suggest that the Guardian of Nature appears in the guise of a gentle breeze, nurturing the flora of the enchanted forests.",
                 {"True", "False"}, "The Guardian of Nature is believed to manifest in the form of a majestic stag, roaming the enchanted forests.", 1, "True/False");

    Question q84("According to ancient tales, the Guardian of Secrets keeps vigil over the Enigma's Abyss, safeguarding ancient mysteries hidden within the depths.",
                 {"True", "False"}, "Legends claim that the Guardian of Secrets dwells within the depths of the Enigma's Abyss, guarding the entrance to the lost city.", 0, "True/False");

    Question q85("The Guardian of Time is rumored to have control over the past, present, and future, able to manipulate time at will.",
                 {"True", "False"}, "According to folklore, the Guardian of Time is said to possess the ability to alter the flow of time itself.", 0, "True/False");

    Question q86("The Guardian of Dreams is rumored to reside within the ethereal realm known as the Dreamer's Nexus. What do legends claim the Guardian of Dreams protects?",
                 {"The dreamscapes of the sleeping", "The boundaries between reality and dream", "The memories of forgotten dreams", "The source of the dreamer's power"},
                 "According to village lore, the Guardian of Dreams watches over the dreamscapes of the sleeping, ensuring their safety and tranquility.", 0, "MCQ");

    Question q87("Legends speak of the Guardian of Shadows, a spectral entity said to haunt the shadowed alleyways of the Twilight City. What is the Guardian of Shadows believed to conceal?",
                 {"The secrets of the night", "The passage to the underworld", "The souls of the departed", "The truth behind illusions"},
                 "Whispers in the Twilight City suggest that the Guardian of Shadows conceals the truth behind illusions, veiling reality in shadows.", 3, "MCQ");

    Question q88("The Guardian of Fire is said to make its home within the fiery depths of the Volcanic Forge. What do tales claim the Guardian of Fire protects?",
                 {"The flames of creation", "The gateway to the inferno", "The ancient artifacts of flame", "The balance of elemental forces"},
                 "According to folklore, the Guardian of Fire protects the ancient artifacts of flame, ensuring they remain safe from harm.", 2, "MCQ");

    Question q89("According to village lore, the Guardian of the Sea is believed to possess the ability to control the ocean's tides. What do legends claim the Guardian of the Sea watches over?",
                 {"The lost treasures of the deep", "The souls of sailors lost at sea", "The balance of marine ecosystems", "The secrets hidden beneath the waves"},
                 "Whispers among sailors suggest that the Guardian of the Sea watches over the balance of marine ecosystems, ensuring harmony in the ocean.", 2, "MCQ");

    Question q90("The Guardian of Light is rumored to manifest in the form of a radiant beacon atop the Tower of Illumination. What is the Guardian of Light believed to illuminate?",
                 {"The path to enlightenment", "The darkness within the soul", "The hidden truths of the world", "The way through the storm"},
                 "According to folklore, the Guardian of Light illuminates the path to enlightenment, guiding seekers toward inner truth.", 0, "MCQ");

    Question q91("Legends speak of the Guardian of Frost, a mystical being said to wield control over icy winds. What do tales claim the Guardian of Frost protects?",
                 {"The heart of the Frozen Wastes", "The souls trapped in eternal ice", "The ancient artifacts of frost", "The balance of winter's embrace"},
                 "According to local lore, the Guardian of Frost protects the heart of the Frozen Wastes, ensuring the balance of winter's embrace.", 3, "MCQ");

    Question q92("Whispers among the villagers suggest that the Guardian of Nature appears in the form of a gentle zephyr. What do legends claim the Guardian of Nature nurtures?",
                 {"The seeds of new beginnings", "The spirits of the forest", "The harmony of the natural world", "The wisdom of the ancient trees"},
                 "It is said that the Guardian of Nature nurtures the harmony of the natural world, ensuring balance among its elements.", 2, "MCQ");

    Question q93("According to ancient tales, the Guardian of Secrets keeps vigil over the Enigma's Abyss, safeguarding ancient mysteries hidden within its depths. What do legends claim the Guardian of Secrets conceals?",
                 {"The keys to forbidden knowledge", "The echoes of forgotten whispers", "The gateway to other realms", "The truth behind reality's veil"},
                 "Legends claim that the Guardian of Secrets conceals the echoes of forgotten whispers, guarding them from those who seek forbidden knowledge.", 1, "MCQ");

    Question q94("The Guardian of Time is said to dwell within the Temporal Sanctum, where the threads of destiny converge. What do tales claim the Guardian of Time oversees?",
                 {"The passage of cosmic cycles", "The tapestry of fate", "The boundaries of eternity", "The birth of new timelines"},
                 "According to folklore, the Guardian of Time oversees the tapestry of fate, weaving the threads of destiny through the ages.", 1, "MCQ");

    Question q95("Legends speak of the Guardian of Dreams, a celestial entity said to watch over the realm of slumber. What do tales claim the Guardian of Dreams safeguards?",
                 {"The dreams of the innocent", "The gates of the Dreamer's Realm", "The memories of past dreams", "D. The source of imagination"},
                 "Whispers among dreamers suggest that the Guardian of Dreams safeguards the gates of the Dreamer's Realm, protecting it from unwelcome intruders.", 1, "MCQ");

    Question q96("The Guardian of Dreams is said to dwell within the deepest caverns of the Dreamer's Abyss.",
                 {"True", "False"}, "According to folklore, the Guardian of Dreams is rumored to make its home within the ethereal realm known as the Dreamer's Nexus.", 1, "True/False");

    Question q97("Legends claim that the Guardian of Shadows can manipulate shadows to deceive its adversaries.",
                 {"True", "False"}, "Whispers among the villagers suggest that the Guardian of Shadows conceals the truth behind illusions, veiling reality in shadows.", 0, "True/False");

    Question q98("The Guardian of Fire is believed to protect the ancient artifacts of flame within the icy caverns at the heart of the Frostbite Mountains.",
                 {"True", "False"}, "According to folklore, the Guardian of Fire protects the ancient artifacts of flame, ensuring they remain safe from harm.", 1, "True/False");

    Question q99("According to village lore, the Guardian of the Sea watches over the balance of marine ecosystems, ensuring harmony in the ocean.",
                 {"True", "False"}, "Whispers among sailors suggest that the Guardian of the Sea watches over the lost treasures of the deep.", 0, "True/False");

    Question q100("The Guardian of Light is rumored to manifest in the form of a radiant phoenix, guiding ships through stormy waters.",
                  {"True", "False"}, "According to folklore, the Guardian of Light illuminates the path to enlightenment, guiding seekers toward inner truth.", 1, "True/False");

    Question q101("Legends speak of the Guardian of Frost, a mystical being said to command the icy winds and freezing temperatures of the Frozen Wastes.",
                  {"True", "False"}, "According to local lore, the Guardian of Frost protects the heart of the Frozen Wastes, ensuring the balance of winter's embrace.", 0, "True/False");

    Question q102("Whispers among the villagers suggest that the Guardian of Nature nurtures the harmony of the natural world, ensuring balance among its elements.",
                  {"True", "False"}, "According to local lore, the Guardian of Nature appears in the form of a gentle breeze, nurturing the flora of the enchanted forests.", 0, "True/False");

    Question q103("According to ancient tales, the Guardian of Secrets conceals the echoes of forgotten whispers, guarding them from those who seek forbidden knowledge.",
                  {"True", "False"}, "Legends claim that the Guardian of Secrets keeps vigil over the Enigma's Abyss, safeguarding ancient mysteries hidden within its depths.", 0, "True/False");

    Question q104("The Guardian of Time is said to oversee the tapestry of fate, weaving the threads of destiny through the ages.",
                  {"True", "False"}, "According to folklore, the Guardian of Time dwells within the Temporal Sanctum, where the threads of destiny converge.", 0, "True/False");

    Question q105("Legends speak of the Guardian of Dreams, a celestial entity said to safeguard the gates of the Dreamer's Realm.",
                  {"True", "False"}, "Whispers among dreamers suggest that the Guardian of Dreams safeguards the dreams of the innocent.", 1, "True/False");
    Question q106("The Guardian of Dreams is rumored to reside within the ethereal realm known as the Dreamer's Nexus. What do legends claim the Guardian of Dreams protects?", {"A. The dreamscapes of the sleeping", "B. The boundaries between reality and dream", "C. The memories of forgotten dreams", "D. The source of the dreamer's power"}, "According to village lore, the Guardian of Dreams watches over the dreamscapes of the sleeping, ensuring their safety and tranquility.", 0, "MCQ");

    Question q107("Legends speak of the Guardian of Shadows, a spectral entity said to haunt the shadowed alleyways of the Twilight City. What is the Guardian of Shadows believed to conceal?",
                  {"The secrets of the night", "The passage to the underworld", "The souls of the departed", "The truth behind illusions"},
                  "Whispers in the Twilight City suggest that the Guardian of Shadows conceals the truth behind illusions, veiling reality in shadows.", 3, "MCQ");

    Question q108("The Guardian of Fire is said to make its home within the fiery depths of the Volcanic Forge. What do tales claim the Guardian of Fire protects?",
                  {"The flames of creation", "The gateway to the inferno", "The ancient artifacts of flame", "The balance of elemental forces"},
                  "According to folklore, the Guardian of Fire protects the ancient artifacts of flame, ensuring they remain safe from harm.", 2, "MCQ");

    Question q109("According to village lore, the Guardian of the Sea is believed to possess the ability to control the ocean's tides. What do legends claim the Guardian of the Sea watches over?",
                  {"The lost treasures of the deep", "The souls of sailors lost at sea", "The balance of marine ecosystems", "The secrets hidden beneath the waves"},
                  "Whispers among sailors suggest that the Guardian of the Sea watches over the balance of marine ecosystems, ensuring harmony in the ocean.", 2, "MCQ");

    Question q110("The Guardian of Light is rumored to manifest in the form of a radiant beacon atop the Tower of Illumination. What is the Guardian of Light believed to illuminate?",
                  {"The path to enlightenment", "The darkness within the soul", "The hidden truths of the world", "The way through the storm"},
                  "According to folklore, the Guardian of Light illuminates the path to enlightenment, guiding seekers toward inner truth.", 0, "MCQ");

    // Add the questions to the question bank
    questions.push_back(q1);
    questions.push_back(q2);
    questions.push_back(q3);
    questions.push_back(q4);
    questions.push_back(q5);
    questions.push_back(q6);
    questions.push_back(q7);
    questions.push_back(q8);
    questions.push_back(q9);
    questions.push_back(q10);
    questions.push_back(q11);
    questions.push_back(q12);
    questions.push_back(q13);
    questions.push_back(q14);
    questions.push_back(q15);
    questions.push_back(q16);
    questions.push_back(q17);
    questions.push_back(q18);
    questions.push_back(q19);
    questions.push_back(q20);
    questions.push_back(q21);
    questions.push_back(q22);
    questions.push_back(q23);
    questions.push_back(q24);
    questions.push_back(q25);
    questions.push_back(q26);
    questions.push_back(q27);
    questions.push_back(q28);
    questions.push_back(q29);
    questions.push_back(q30);
    questions.push_back(q31);
    questions.push_back(q32);
    questions.push_back(q33);
    questions.push_back(q34);
    questions.push_back(q35);
    questions.push_back(q36);
    questions.push_back(q37);
    questions.push_back(q38);
    questions.push_back(q39);
    questions.push_back(q40);
    questions.push_back(q41);
    questions.push_back(q42);
    questions.push_back(q43);
    questions.push_back(q44);
    questions.push_back(q45);
    questions.push_back(q46);
    questions.push_back(q47);
    questions.push_back(q48);
    questions.push_back(q49);
    questions.push_back(q50);
    questions.push_back(q51);
    questions.push_back(q52);
    questions.push_back(q53);
    questions.push_back(q54);
    questions.push_back(q55);
    questions.push_back(q56);
    questions.push_back(q57);
    questions.push_back(q58);
    questions.push_back(q59);
    questions.push_back(q60);
    questions.push_back(q61);
    questions.push_back(q62);
    questions.push_back(q63);
    questions.push_back(q64);
    questions.push_back(q65);
    questions.push_back(q66);
    questions.push_back(q67);
    questions.push_back(q68);
    questions.push_back(q69);
    questions.push_back(q70);
    questions.push_back(q71);
    questions.push_back(q72);
    questions.push_back(q73);
    questions.push_back(q74);
    questions.push_back(q75);
    questions.push_back(q76);
    questions.push_back(q77);
    questions.push_back(q78);
    questions.push_back(q79);
    questions.push_back(q80);
    questions.push_back(q81);
    questions.push_back(q82);
    questions.push_back(q83);
    questions.push_back(q84);
    questions.push_back(q85);
    questions.push_back(q86);
    questions.push_back(q87);
    questions.push_back(q88);
    questions.push_back(q89);
    questions.push_back(q90);
    questions.push_back(q91);
    questions.push_back(q92);
    questions.push_back(q93);
    questions.push_back(q94);
    questions.push_back(q95);
    questions.push_back(q96);
    questions.push_back(q97);
    questions.push_back(q98);
    questions.push_back(q99);
    questions.push_back(q100);
    questions.push_back(q101);
    questions.push_back(q102);
    questions.push_back(q103);
    questions.push_back(q104);
    questions.push_back(q105);
    questions.push_back(q106);
    questions.push_back(q107);
    questions.push_back(q108);
    questions.push_back(q109);
    questions.push_back(q110);

    return questions;
}

// Method to generate a random question from the question bank
Question QuestionBank::generateQuestion() {
    // Check if the list of questions is empty
    if (questions.isEmpty()) {
        // Print debug statement indicating that the list is empty
        qDebug() << "Warning: The list of questions is empty!";
        // Return a default-constructed question
        return Question();
    }

    // Seed the random number generator
    srand(time(NULL));

    // Generate a random index from 0 to questions.size() - 1
    int index = rand() % questions.size();

    // Initialize an iterator to the beginning of the list
    auto it = questions.begin();

    // Initialize a variable to store the current question
    Question currentQuestion;

    // Iterate to the random index
    for (int i = 0; i < index && it != questions.end(); ++i, ++it);

    // Check if the iterator is still valid
    if (it != questions.end()) {
        // Assign the value pointed to by the iterator to currentQuestion
        currentQuestion = *it;
    }

    // Return the randomly selected question
    return currentQuestion;
}

// Method to remove a specific question from the question bank
void QuestionBank::removeQuestion(const Question& question){
    questions.removeOne(question); // Remove the specified question from the list
}
