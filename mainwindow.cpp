#include "mainwindow.h"
#include "ui_mainwindow.h"

//--------------------------------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , score(0)
    , maxQuestions(0)
    , animationInProgress(false)
    , consecutiveCorrectAnswers(0)

{
    ui->setupUi(this);;
    score = 0; // Initial score
    //Add the questions and generate them randomly
    db.loadQuestion();

    //set font color for BEGIN QUIZ
    ui->promptLabel->setStyleSheet("color: red; background-color: transparent;");
    ui->quitBtn->setToolTip("Quit Game");
    ui->musicButton->setIcon(QIcon(":/sounds/musical-note-symbol.ico"));

    //Set backround in the main page
    ui->tabWidget->widget(0)->setStyleSheet("background-image: url(:/pictures/pictures/menuImage.png);");
    ui->tabWidget->widget(1)->setStyleSheet("background-image: url(:/pictures/pictures/menuImage.png);");

    // Get the original pixmap from the instructionImage label
    QPixmap originalPixmap = ui->instructionImage->pixmap(Qt::ReturnByValue);

    // Create a transparent black pixmap with the same size as the original pixmap
    QPixmap dimmedPixmap(originalPixmap.size());
    dimmedPixmap.fill(QColor(0, 0, 0, 128)); // Adjust alpha (last parameter) to control opacity

    // Use QPainter to draw the dimmed pixmap onto the original pixmap
    QPainter painter(&originalPixmap);
    painter.drawPixmap(0, 0, dimmedPixmap);

    // Set the combined pixmap as the pixmap for the instructionImage label
    ui->instructionImage->setPixmap(originalPixmap);

    playBackgroundMusic();
    isMusicPlaying = true;
    buttonSoundsEnabled = true;
}
//--------------------------------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;

    //Stop the background music when the window is destroyed
    backgroundMusic.stop();
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::fadeInWidget() {

    hideQuizWindow();

    // If an animation is already in progress, return early
    if (animationInProgress) {
        return;
    }

    // Create a graphics opacity effect for the tab widget
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(ui->tabWidget);

    // Set the starting opacity to fully transparent (0.0)
    opacityEffect->setOpacity(0.0);

    // Apply the opacity effect to the tab widget
    ui->tabWidget->setGraphicsEffect(opacityEffect);
    //tabWidget->setGraphicsEffect(opacityEffect);

    // Set the flag to indicate that an animation is in progress
    animationInProgress = true;

    // Create a property animation to gradually increase the opacity
    QPropertyAnimation *animation = new QPropertyAnimation(opacityEffect, "opacity");

    // Set the duration of the animation (in milliseconds)
    animation->setDuration(1000); // Adjust duration as needed

    // Set the ending opacity to fully opaque (1.0)
    animation->setEndValue(1.0);

    // Set the easing curve for a smooth animation
    animation->setEasingCurve(QEasingCurve::InOutQuad); // Adjust easing curve as needed

    // Connect the finished() signal of the animation to a slot
    QObject::connect(animation, &QPropertyAnimation::finished, [=]() {
        // Reset the flag to indicate that no animation is in progress
        animationInProgress = false;
        // Ensure the tab widget is visible after the animation

        ui->tabWidget->setVisible(true);
    });
    // Start the animation
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::fadeOutWidget(QTabWidget *tabWidget) {

    // If an animation is already in progress, return early
    if (animationInProgress) {
        return;
    }
    // Set the flag to indicate that an animation is in progress
    animationInProgress = true;
    // Create a graphics opacity effect for the tab widget
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(tabWidget);

    // Set the starting opacity to fully opaque (1.0)
    opacityEffect->setOpacity(1.0);

    // Apply the opacity effect to the tab widget
    tabWidget->setGraphicsEffect(opacityEffect);

    // Create a property animation to gradually reduce the opacity
    QPropertyAnimation *animation = new QPropertyAnimation(opacityEffect, "opacity");

    // Set the duration of the animation (in milliseconds)
    animation->setDuration(1000); // Adjust duration as needed

    // Set the ending opacity to fully transparent (0.0)
    animation->setEndValue(0.0);

    // Set the easing curve for a smooth animation
    animation->setEasingCurve(QEasingCurve::InOutQuad); // Adjust easing curve as needed

    // Connect the finished() signal of the animation to a slot
    QObject::connect(animation, &QPropertyAnimation::finished, [=]() {
        // Hide the tab widget after the animation completes
        animationInProgress = false;
        tabWidget->setVisible(false);
        generateIntroductionText();
    });
    // Start the animation
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
//--------------------------------------------------------------------------------------------------------------------------
// Slot method to show the help button with dimming effect and prompt label
void MainWindow::showHelpButton() {

    if (!helpButtonVisible) {

        // Create a semi-transparent overlay widget to dim the background and create a fog effect
        overlayWidget = new QWidget(this);
        overlayWidget->setGeometry(0, 0, width(), height());
        overlayWidget->setStyleSheet("background-color: rgba(0, 128, 0, 0.1);"); // Adjust the alpha value for a dimmer effect
        overlayWidget->setVisible(true);

        // Create an animation to make the help button fidget on the screen
        blinkAnimation = new QPropertyAnimation(helpButton, "geometry");
        blinkAnimation->setDuration(2000); // Adjust the duration for a slower blinking effect
        blinkAnimation->setStartValue(QRect(width() / 2 - 42, height() / 2 - 42, 84, 84)); // Adjust the initial position of the button to the center
        blinkAnimation->setEndValue(QRect(width() / 2 - 52, height() / 2 - 52, 104, 104)); // Adjust the end position and size of the button
        blinkAnimation->setLoopCount(-1); // Set the animation to loop indefinitely
        blinkAnimation->start();

        // Set the icon and size of the helpButton
        helpButton->setIcon(QIcon(":/pictures/pictures/lock.jpg"));
        helpButton->setIconSize(QSize(125, 125)); // Set the icon size
        helpButton->setFixedSize(125, 125); // Set the button size
        helpButton->move(width() / 2 - 52, height() / 2 - 52); // Move the button to the center
        helpButton->raise(); // Raise the helpButton above the overlayWidget

        // Adjust the font size, weight, and position of the prompt label
        promptLabel->setText("Bravo! You've unlocked the help feature. Click to unlock.");
        promptLabel->setStyleSheet("color: green; background: white; font-size: 45px; font-weight: bold;"); // Adjust font size, style, and weight
        promptLabel->setAlignment(Qt::AlignCenter); // Center-align the text
        promptLabel->setGeometry(0, height() / 6, width(), height() / 8); // Position the label lower
        promptLabel->raise(); // Raise the promptLabel above the overlayWidget

        helpButton->setVisible(true);
        promptLabel->setVisible(true);
        helpButtonVisible = true; // Update the flag
    }
}
//----------------------------------------------------------------------------------------------------------------
// Slot method to handle the click event of the help button
void MainWindow::unlockHelp() {
    // Remove the overlay widget, prompt label, and help button from the screen
    // Set the visibility of the help button to false
    helpButton->setVisible(false);
    promptLabel->setVisible(false);

    overlayWidget->setVisible(false);

    eliminateChoices();

    blinkAnimation->stop();

    // Reset the consecutive correct answers counter
    consecutiveCorrectAnswers = 0;
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::eliminateChoices() {
    if (currentQuestion.getQuestionType() == "MCQ") {
        // Get the indices of the correct and incorrect answer choices
        int correctIndex = currentQuestion.getCorrectIndex();
        QVector<int> incorrectIndices;
        for (int i = 0; i < currentQuestion.getAnswerOption().size(); ++i) {
            if (i != correctIndex) {
                incorrectIndices.push_back(i);
            }
        }

        // Randomly select two incorrect answer choices to eliminate
        std::random_shuffle(incorrectIndices.begin(), incorrectIndices.end());
        int choice1 = incorrectIndices.at(0);
        int choice2 = incorrectIndices.at(1);

        // Hide the buttons corresponding to the eliminated choices
        if (choice1 == 0) {
            answerButton1->setVisible(false);
        } else if (choice1 == 1) {
            answerButton2->setVisible(false);
        } else if (choice1 == 2) {
            answerButton3->setVisible(false);
        } else if (choice1 == 3) {
            answerButton4->setVisible(false);
        }

        if (choice2 == 0) {
            answerButton1->setVisible(false);
        } else if (choice2 == 1) {
            answerButton2->setVisible(false);
        } else if (choice2 == 2) {
            answerButton3->setVisible(false);
        } else if (choice2 == 3) {
            answerButton4->setVisible(false);
        }
    }
    if(currentQuestion.getQuestionType() == "True/False"){
        hintNum += 2;
        hintLabel->setText(QString::number(hintNum));
        showHintDisplay();
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::showHintDisplay() {
    // Create the QLabel for the "+2" text
    QLabel *hintText = new QLabel("+2", this);
    hintText->setStyleSheet("color: green; font-size: 36px; font-weight: bold;");
    hintText->setGeometry(width() / 2 - 40, height() / 2 - 40, 400, 400);
    hintText->setVisible(true);

    // Create the QLabel for the bulb picture
    QLabel *bulbIcon = new QLabel(this);
    bulbIcon->setPixmap(QPixmap(":/pictures/pictures/light_bulb.jpg").scaled(80, 80));
    bulbIcon->setGeometry(width() / 2 + 40, height() / 2 - 40, 400, 400);
    bulbIcon->setVisible(true);

    // Add a QTimer to handle the disappearance of the hint display after a short duration
    QTimer::singleShot(1000, [=]() {
        hintText->setVisible(false);
        bulbIcon->setVisible(false);
        hintText->deleteLater(); // Free up memory
        bulbIcon->deleteLater(); // Free up memory
    });
}
//--------------------------------------------------------------------------------------------------------------------------
// Implementation of getCurrentLevel() function to retrieve the current level
Level MainWindow::getCurrentLevel()
{
    return currentLevel;
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::generateIntroductionText()
{
    index = 0; // Reset index to 0
    // Load background image
    QImage backgroundImage(":/pictures/pictures/image.png");

    // Create a QLabel to display the background image
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap::fromImage(backgroundImage));
    backgroundLabel->setGeometry(0, 0, width(), height());
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setVisible(true); // Set background label visible

    // Add semi-transparent overlay to make text more readable
    overlay = new QFrame(this);
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 150);");
    overlay->setGeometry(0, 0, width(), height());
    overlay->setVisible(true); // Set overlay visible

    // Create QTextEdit widget for the introduction text
    introductionText = new QTextEdit(this);
    introductionText->setStyleSheet("color: white; font-size: 25px; background-color: transparent");
    introductionText->setReadOnly(true);
    introductionText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    introductionText->setGeometry(100, 100, width() - 200, height() - 200);
    introductionText->setVisible(true); // Set introduction text visible

    // Create timer for gradually generating the text
    textTimer = new QTimer(this);
    connect(textTimer, &QTimer::timeout, this, [=]() {

        QString fullText = "In the depths of the Scottish Highlands, nestled among the mist-shrouded moors, "
                           "lies the remote village of Glenhaven. Once a bustling hub of trade and prosperity, Glenhaven now harbors a dark secret veiled by centuries-old mysteries. Legend has it that beneath the ancient ruins of "
                           "Dunhaven Castle lies the key to unlocking unimaginable power—a relic known as the Emerald Cipher. "
                           "For generations, the villagers have whispered tales of the Emerald Cipher, passing down cryptic clues hidden within riddles and folklore. But despite countless attempts, the cipher remains unsolved, its secrets guarded by the spirits of the past. "
                           "As a daring adventurer seeking fame and fortune, you arrive in Glenhaven determined to unravel the enigma of the Emerald Cipher. Armed with wits and curiosity, you set forth on a quest to decipher the mysteries of Dunhaven Castle and uncover the truth hidden within its ancient walls.";
        if (index < fullText.length()) {
            introductionText->insertPlainText(fullText.mid(index, 1));
            ++index;
        } else {
            textTimer->stop(); // Stop the timer when all text is generated
            showQuizWindow(); // Call openQuizWindow when text is done loading
        }
    });

    // Start the timer with a delay of 100 milliseconds between each character
    textTimer->start(100);

    // Create "Skip Intro" button
    skipIntroButton = new QPushButton("Skip Intro", this);
    skipIntroButton->setStyleSheet("color: white; background-color: rgba(0, 0, 0, 50);");
    skipIntroButton->setGeometry(width() - 150, 50, 100, 50);
    skipIntroButton->setVisible(true); // Set skip intro button visible

    // Connect the "Skip Intro" button's clicked signal to directly transition to the quiz frame
    connect(skipIntroButton, &QPushButton::clicked, this, &MainWindow::showQuizWindow);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::showQuizWindow(){

    maxQuestions = 0;
    score = 0;

    overlay->setVisible(false); //close intro frame
    introductionText->setVisible(false); //close into text
    backgroundLabel->setVisible(false); //close background image;
    textTimer->stop();

    // Load background image
    QImage backgroundImage(":/pictures/pictures/quiz.png");

    // Create a QLabel to display the background image
    quizBackground = new QLabel(this);
    quizBackground->setPixmap(QPixmap::fromImage(backgroundImage));
    quizBackground->setGeometry(0, 0, width(), height());
    quizBackground->setScaledContents(true);
    quizBackground->setVisible(true); // Set background label visible

    // Add semi-transparent overlay to make text more readable
    quizFrame = new QFrame(this);
    quizFrame->setStyleSheet("background-color: rgba(0, 0, 0, 90);");
    quizFrame->setGeometry(0, 0, width(), height());
    quizFrame->setVisible(true); // Set overlay visible

    // Create the hintButton
    hintButton = new QPushButton("Hint", this);
    hintButton->setStyleSheet("color: orange; background-color: white;");
    hintButton->setIcon(QIcon(":/pictures/pictures/light_bulb.jpg"));
    hintButton->setIconSize(QSize(40, 50));
    hintButton->setGeometry(10, 10, 100, 50); // Adjusted coordinates for top-left corner
    hintButton->setVisible(true); // Set hintButton visible
    toggleButtonSounds(hintButton);
    connect(hintButton, &QPushButton::clicked, this, &MainWindow::on_hintBtn_clicked);

    // Create the hintLabel
    hintLabel = new QLabel(QString::number(hintNum), this); // Initialize with the current value of hintNum
    hintLabel->setStyleSheet("color: orange; font-weight: bold; font-size: 25px;"); // Set style for the label
    hintLabel->setGeometry(120, 10, 50, 50); // Adjusted coordinates for the label
    hintLabel->setVisible(true); // Set hintLabel visible

    hintMessage = new QMessageBox(this);
    QFont hfont = hintMessage->font();
    hfont.setPointSize(24); // Increase font size to 24
    hfont.setBold(true); // Set text to bold
    hfont.setItalic(true); // Set text to italic
    hintMessage->setFont(hfont);
    hintMessage->setStyleSheet("QMessageBox { background-color: orange; }");
    int mainWindowWidth = this->width();
    int mainWindowHeight = this->height();
    hintMessage->setGeometry(mainWindowWidth / 8, mainWindowHeight / 8, mainWindowWidth/ 2, mainWindowHeight);

    // Calculate the coordinates for top center
    int labelWidth = 100; // Width of the label
    int labelHeight = 50; // Height of the label
    int xCoordinate = (width() - labelWidth) / 2; // Center horizontally
    int yCoordinate = 10; // 10 pixels from the top

    // Create QLabel for displaying score
    scoreDisplay = new QLabel("Score: 0", this); // Initial score set to 0

    // Set font to bold
    QFont font = scoreDisplay->font();
    font.setBold(true);
    font.setItalic(true);
    font.setPointSize(20); // Set font size to 16 points
    scoreDisplay->setFont(font);
    scoreDisplay->setStyleSheet("color: orange; background-color: transparent");
    scoreDisplay->setGeometry(xCoordinate, yCoordinate, labelWidth, labelHeight);
    scoreDisplay->setVisible(true); // Set score label visible
    scoreDisplay->setText(QString::number(score)); // Update the score label text

    // Create QLabel for displaying the score label
    scoreLabel = new QLabel("Score: ", this);
    // Set font and style for the score label
    scoreLabel->setFont(font); // Reuse the font from scoreDisplay
    scoreLabel->setStyleSheet("color: orange; background-color: transparent");
    // Adjust the geometry for the score label
    int labelX = xCoordinate - labelWidth - 10; // Adjust horizontal position
    scoreLabel->setGeometry(labelX, yCoordinate, labelWidth, labelHeight);
    scoreLabel->setVisible(true);

    // Create "Quit Quiz" button
    quitQuizButton = new QPushButton("Menu", this);
    quitQuizButton->setStyleSheet("color: orange; background-color: white;");
    quitQuizButton->setGeometry(width() - 150, yCoordinate, 100, 50);
    quitQuizButton->setVisible(true);

    // Connect the "Quit Quiz" button's clicked signal to the fadeIn() slot
    toggleButtonSounds(quitQuizButton);
    connect(quitQuizButton, &QPushButton::clicked, this, &MainWindow::fadeInWidget);

    // Calculate the position for the nextButton
    int buttonW = 50; // Adjust width as needed
    int buttonH = 50; // Adjust height as needed
    int buttonX = width() - buttonW - 10; // 10 pixels from the right edge
    int buttonY = height() - buttonH - 10; // 10 pixels from the bottom edge

    // Create the nextButton
    nextButton = new QPushButton("", this);

    // Retrieve the standard icon for the arrow pointing right from the style
    QStyle* style = nextButton->style();
    QIcon nextIcon = style->standardIcon(QStyle::SP_ArrowForward);
    nextButton->setIcon(nextIcon);
    // Set the text to an empty string
    nextButton->setText("");
    // Set stylesheet for color and background
    nextButton->setStyleSheet("color: orange; background-color: white;");
    // Set icon size
    nextButton->setIconSize(QSize(buttonW, buttonH));
    nextButton->setVisible(true);
    // Set the geometry
    nextButton->setGeometry(buttonX, buttonY, buttonW, buttonH);
    toggleButtonSounds(nextButton);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::nextBtnOnClick);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::updateProgress);

    submit = new QPushButton("", this);
    submit->setText("Finish Quest");
    submit->setStyleSheet("color: orange; background-color: white;");
    submit->setGeometry(width() - buttonW - 50, buttonY, 100, buttonH);
    toggleButtonSounds(submit);
    connect(submit, &QPushButton::clicked, this, &MainWindow::showFeedbackWindow);

    // Calculate the y-coordinate for the bottom-left corner
    int windowHeight = height();
    int btnH = 50; // Adjust button height as needed
    int padding = 10; // Adjust padding as needed
    int yCoord = windowHeight - btnH- padding;

    // Create the skipButton and set its properties
    skipButton = new QPushButton("Skip", this);
    skipButton->setStyleSheet("color: orange; background-color: white;");
    skipButton->setIcon(QIcon(":/pictures/pictures/skip.png"));
    skipButton->setIconSize(QSize(50, 60));
    skipButton->setGeometry(10, yCoord, 100, btnH); // Set coordinates for bottom-left corner
    skipButton->setVisible(true); // Set skip button visible
    toggleButtonSounds(skipButton);
    connect(skipButton, &QPushButton::clicked, this, &MainWindow::on_skipBtn_clicked);

    // Create the skipLabel
    skipLabel = new QLabel(QString::number(numSkip), this); // Initialize with the current value of hintNum
    skipLabel->setStyleSheet("color: orange; font-weight: bold; font-size: 25px;");
    skipLabel->setGeometry(120, yCoord, 50, 50); // Adjusted coordinates for the label
    skipLabel->setVisible(true); // Set skipLabel visible

    // Load questions and display them in a scrollable text area
    questionTextEdit = new QTextEdit(this);
    questionTextEdit->setStyleSheet("color: white; font-size: 20px; background-color: transparent; border: 2px solid #50C878;");
    questionTextEdit->setReadOnly(true);
    questionTextEdit->setAlignment(Qt::AlignCenter);
    questionTextEdit->setGeometry(50, 50, width() - 100, height() - 100);
    questionTextEdit->setVisible(true);

    // Create a scroll area to contain the question text
    scrollArea = new QScrollArea(this);
    int scrollWidth = width() - 200; // Adjust width as needed
    int scrollHeight = height() - 800; // Adjust height as needed
    int scrollX = (width() - scrollWidth) / 2; // Center horizontally
    int scrollY = (height() - scrollHeight) / 8; // Adjust vertical position
    scrollArea->setGeometry(scrollX, scrollY, scrollWidth, scrollHeight);

    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(questionTextEdit);
    scrollArea->setVisible(true);
    scrollArea->setStyleSheet("background-color: transparent; border: 2px solid #50C878;");

    // Define button size and position
    int buttonWidth = 350;
    int buttonHeight = 70;
    int buttonSpacing = 10; // Adjust spacing between buttons as needed
    int buttonStartY = height() / 3 + 50; // Start a bit below the middle of the window

    // Calculate starting position for the first button
    int startX = (width() - buttonWidth) / 2;

    // Define the position for the circles
    int circleRadius = 13; // Adjust radius as needed

    // Calculate the diameter of the circles
    int circleDiameter = 2 * circleRadius * 3; // Increase the diameter by a factor of 3

    // Set position for optionCircleA (slightly below the middle and aligned with the button)
    int circleX = startX - circleDiameter - buttonSpacing; // Align with the answer button
    //int circleY = buttonStartY + (buttonHeight - circleDiameter) / 2; // Align vertically with the button

    // Set up buttons and circles with labels
    answerButton1 = new QPushButton(this);
    answerButton1->setGeometry(startX, buttonStartY, buttonWidth, buttonHeight);
    answerButton1->setVisible(true);
    connect(answerButton1, &QPushButton::clicked, this, &MainWindow::answerButton1_OnClick);

    optionCircleA = new QLabel(this);
    optionCircleA->setGeometry(circleX, buttonStartY + (buttonHeight - circleDiameter) / 2, circleDiameter, circleDiameter);
    optionCircleA->setText("A:");
    optionCircleA->setAlignment(Qt::AlignCenter);
    optionCircleA->setStyleSheet("QLabel { background-color: green; color: white; font-weight: bold; border-radius: " + QString::number(circleDiameter / 2) + "px; }");
    optionCircleA->setVisible(true);

    // Label for button1
    correctAnswerLabel1 = new QLabel(this);
    correctAnswerLabel1->setText("");
    correctAnswerLabel1->setGeometry(startX + buttonWidth  + buttonSpacing, buttonStartY, 750, buttonHeight);
    correctAnswerLabel1->setVisible(false);

    // Set the font of the label
    QFont answerFont1 = correctAnswerLabel1->font();
    answerFont1.setPointSize(12);
    correctAnswerLabel1->setFont(answerFont1);

    // Update vertical position for the next button and circle
    buttonStartY += buttonHeight + buttonSpacing;

    answerButton2 = new QPushButton(this);
    answerButton2->setGeometry(startX, buttonStartY, buttonWidth, buttonHeight);
    answerButton2->setVisible(true);
    connect(answerButton2, &QPushButton::clicked, this, &MainWindow::answerButton2_OnClick);

    optionCircleB = new QLabel(this);
    optionCircleB->setGeometry(circleX, buttonStartY + (buttonHeight - circleDiameter) / 2, circleDiameter, circleDiameter);
    optionCircleB->setAlignment(Qt::AlignCenter);
    optionCircleB->setText("B:");
    optionCircleB->setStyleSheet("QLabel { background-color: green; color: white; font-weight: bold; border-radius: " + QString::number(circleDiameter / 2) + "px; }");
    optionCircleB->setVisible(true);

    // Label for button2
    correctAnswerLabel2 = new QLabel(this);
    correctAnswerLabel2->setText("");
    correctAnswerLabel2->setGeometry(startX + buttonWidth + buttonSpacing, buttonStartY, 750, buttonHeight);
    correctAnswerLabel2->setVisible(false);

    // Set the font of the label
    QFont answerFont2 = correctAnswerLabel2->font();
    answerFont2.setPointSize(12);
    correctAnswerLabel2->setFont(answerFont2);

    // Update vertical position for the next button and circle
    buttonStartY += buttonHeight + buttonSpacing;

    answerButton3 = new QPushButton(this);
    answerButton3->setGeometry(startX, buttonStartY, buttonWidth, buttonHeight);
    answerButton3->setVisible(true);
    connect(answerButton3, &QPushButton::clicked, this, &MainWindow::answerButton3_OnClick);

    optionCircleC = new QLabel(this);
    optionCircleC->setGeometry(circleX, buttonStartY + (buttonHeight - circleDiameter) / 2, circleDiameter, circleDiameter);
    optionCircleC->setAlignment(Qt::AlignCenter);
    optionCircleC->setText("C:");
    optionCircleC->setStyleSheet("QLabel { background-color: green; color: white; font-weight: bold; border-radius: " + QString::number(circleDiameter / 2) + "px; }");
    optionCircleC->setVisible(true);

    // Label for button3
    correctAnswerLabel3 = new QLabel(this);
    correctAnswerLabel3->setText("");
    correctAnswerLabel3->setGeometry(startX + buttonWidth + buttonSpacing, buttonStartY, 750, buttonHeight);
    correctAnswerLabel3->setVisible(false);

    // Set the font of the label
    QFont answerFont3 = correctAnswerLabel3->font();
    answerFont3.setPointSize(12);
    correctAnswerLabel3->setFont(answerFont3);

    // Update vertical position for the next button and circle
    buttonStartY += buttonHeight + buttonSpacing;

    answerButton4 = new QPushButton(this);
    answerButton4->setGeometry(startX, buttonStartY, buttonWidth, buttonHeight);
    answerButton4->setVisible(true);
    connect(answerButton4, &QPushButton::clicked, this, &MainWindow::answerButton4_OnClick);

    optionCircleD = new QLabel(this);
    optionCircleD->setGeometry(circleX, buttonStartY + (buttonHeight - circleDiameter) / 2, circleDiameter, circleDiameter);
    optionCircleD->setAlignment(Qt::AlignCenter);
    optionCircleD->setText("D:");
    optionCircleD->setStyleSheet("QLabel { background-color: green; color: white; font-weight: bold; border-radius: " + QString::number(circleDiameter / 2) + "px; }");
    optionCircleD->setVisible(true);

    // Label for button4
    correctAnswerLabel4 = new QLabel(this);
    correctAnswerLabel4->setText("");
    correctAnswerLabel4->setGeometry(startX + buttonWidth + buttonSpacing, buttonStartY, 750, buttonHeight);
    correctAnswerLabel4->setVisible(false);

    // Set the font of the label
    QFont answerFont4 = correctAnswerLabel4->font();
    answerFont4.setPointSize(12);
    correctAnswerLabel4->setFont(answerFont4);

    displayQuestion();

    consecutiveCorrectAnswers = 0;
    helpButtonVisible = false;

    helpButton = new QPushButton(this);
    toggleButtonSounds(helpButton);
    connect(helpButton, SIGNAL(clicked()), this, SLOT(unlockHelp()));

    //create a prompt label to inform the player about the special feature
    promptLabel = new QLabel(this);

    progressBarDiameter = 80; // Diameter of the progress bar

    // Calculate the position for the circular progress bar
    int progressBarX = (width() - progressBarDiameter) / 2; // Center horizontally
    int progressBarY = height() - 28 - progressBarDiameter; // Adjusted position for the progress bar

    // Calculate the position and size for the timer label
    int timerLabelWidth = progressBarDiameter; // Same width as the progress bar
    int timerLabelHeight = progressBarDiameter; // Same height as the progress bar
    int timerLabelX = progressBarX; // Center horizontally within the progress bar
    int timerLabelY = progressBarY; // Center vertically within the progress bar

    // Create and initialize the RingProgressBar widget
    progressBar = new RingProgressBar(this);
    progressBar->setValue(0); // Set initial progress value
    progressBar->move(timerLabelX - 10, timerLabelY - 10); // Adjust the position of the progress bar
    progressBar->setVisible(true); // Initially hide the progress bar

    // Create QLabel for displaying the timer
    timerLabel = new QLabel("00:00", this);
    QFont timerFont = timerLabel->font();
    timerFont.setPointSize(16); // Decrease font size for the timer label
    timerLabel->setFont(timerFont);
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setGeometry(timerLabelX, timerLabelY, timerLabelWidth, timerLabelHeight);
    timerLabel->setStyleSheet("background-color: transparent; color: white;"); // Set background color to transparent
    timerLabel->setVisible(true);

    // Calculate the position for the progress bar
    int progressWidth = 500;
    int progressHeight = 20; // Adjust height as needed
    int progressX = timerLabelX - (progressWidth - timerLabelWidth) / 2; // Center align and shift to the left
    int progressY = timerLabelY + timerLabelHeight + 10; // Adjust vertical position below the timer label

    progress = new QProgressBar(this);
    progress->setRange(0, 100); // Set range from 0 to 100
    progress->setValue(0); // Set initial value to 0
    progress->setGeometry(progressX, progressY, progressWidth, progressHeight);
    progress->setStyleSheet("color: white; font-size: 16px; ");
    progress->setOrientation(Qt::Horizontal); // Set progress bar to horizontal
    progress->setVisible(true);

    // Determine the current level
    Level level = getCurrentLevel();

    // Update the timer based on the current level
    updateTimer(level);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::showFeedbackWindow(){

    hideQuizWindow();
    submit->setVisible(false);
    hideCorrectAnswerLabel();

    // Load background image
    QImage backgroundImage(":/pictures/pictures/feedbackBackground.png");

    // Create a QLabel to display the background image
    feedbackBackground = new QLabel(this);
    feedbackBackground->setPixmap(QPixmap::fromImage(backgroundImage));
    feedbackBackground->setGeometry(0, 0, width(), height());
    feedbackBackground->setScaledContents(true);
    feedbackBackground->setVisible(true); // Set background label visible

    // Add semi-transparent overlay to make text more readable
    feedbackFrame = new QFrame(this);
    feedbackFrame->setStyleSheet("background-color: rgba(0, 0, 0, 90);");
    feedbackFrame->setGeometry(0, 0, width(), height());
    feedbackFrame->setVisible(true); // Set overlay visible

    QFont font; // Define your QFont instance
    font.setFamily("Robot"); // Set the font family to Robot
    font.setPointSize(10);   // Set the font size
    font.setBold(true); // Set the font to bold

    // Calculate the position for the retry button
    int buttonWidth = 50; // Adjust width as needed
    int buttonHeight = 50; // Adjust height as needed
    int buttonX = width() - buttonWidth - 10; // 10 pixels from the right edge
    int buttonY = height() - buttonHeight - 10; // 10 pixels from the bottom edge

    // Create retry button
    retryBtn = new QPushButton("", this);

    // Retrieve the standard icon for the retry
    QStyle* style = retryBtn->style();
    QIcon retryIcon = style->standardIcon(QStyle::SP_BrowserReload);
    retryBtn->setIcon(retryIcon);

    // Set the text to an empty string
    retryBtn->setText("");

    // Set stylesheet for color and background
    retryBtn->setStyleSheet("color: black; background-color: white;");

    // Set icon size
    retryBtn->setIconSize(QSize(buttonWidth, buttonHeight));

    // Set retry button geometry
    retryBtn->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);
    retryBtn->setVisible(true);
    toggleButtonSounds(retryBtn);

    connect(retryBtn,&QPushButton::clicked,this,&MainWindow::on_retryButton_clicked);
    connect(retryBtn, &QPushButton::clicked, this, &MainWindow::hideFeedBackWindow);

    // Calculate the position for the retry label
    int labelWidth = 50; // Adjust width as needed
    int labelHeight = 20; // Adjust height as needed
    int labelX = buttonX - labelWidth; // Align to the left of the button
    int labelY = buttonY + (buttonHeight - labelHeight) / 2; // Align vertically with the button

    // Create retry label
    retryLabel = new QLabel(this);
    retryLabel->setText("RETRY");
    retryLabel->setStyleSheet("color: lime");
    retryLabel->setFont(font); // Apply font to retry label
    retryLabel->setAlignment(Qt::AlignCenter); // Center text horizontally
    retryLabel->setGeometry(labelX, labelY, labelWidth, labelHeight);
    retryLabel->setVisible(true);

    // Create the backButton
    backButton = new QPushButton("Go to main page", this);

    // Set the font size of the button's text
    QFont buttonFont = backButton->font();
    buttonFont.setPointSize(16); // Set the desired font size, for example, 16 points
    backButton->setFont(buttonFont);

    // Set other properties of the button
    backButton->setStyleSheet("color: green; background-color: grey;");
    backButton->setGeometry(10, height() - 50 - 10, 160, 50); // Set coordinates for bottom-left corner
    backButton->setVisible(true); // Set button visible
    toggleButtonSounds(backButton);
    connect(backButton, &QPushButton::clicked, this, &MainWindow::fadeInWidget);
    connect(backButton, &QPushButton::clicked, this, &MainWindow::hideFeedBackWindow);


    // Calculate the final score
    double calculatedScore = finalScore.calculateScore(score);

    // Convert the calculated score integer to a QString and concatenate with "%"
    QString scoreText = QString::number(calculatedScore) + "%";

    // Create final score label
    finalScoreLabel = new QLabel(this);
    finalScoreLabel->setText(scoreText); // Set the label text with calculated score followed by "%"
    finalScoreLabel->setVisible(true);

    // Increase label size
    finalScoreLabel->setFont(QFont("Arial", 50)); // Example font, adjust as needed
    finalScoreLabel->setStyleSheet("color: lime"); // Set text color to lime

    // Calculate position for centering the label
    int labelW = 200; // Example width, adjust as needed
    int labelH = 100; // Example height, adjust as needed
    int x = (width() - labelW) / 2; // Center horizontally
    int y = (height() - labelH) / 6 - 50; // Center vertically and move up by 50 pixels

    // Set label geometry
    finalScoreLabel->setGeometry(x, y, labelW, labelH);

    QString feedback;

    if (calculatedScore <= 30){

        feedback = "Your quest for the Emerald Cipher has met with failure, but remeber, this is not the end. "
                   "In the face of adversity, even the greatest adventures stumble and fall. "
                   "Rise from the ashes of defeat and take heart, for there is still much to be gained from this experience. "
                   "For the path to greatness is often littered with missteps and setbacks, and it is how you recover from these challanges that defines your character. ";
    }
    else if(calculatedScore > 30 && calculatedScore <= 40){

        feedback = "The spirits of Glenhaven have turned their gaze away from you, their power and secrets remaining beyond your reach. "
                   "But take heart, brave soul, for this is not the end of your story. "
                   "Remember that failure is not the opposite of success, but rather a necessary part of the journey towards greatness. "
                   "So pick yourself up, dust yourself off, and continue to seek out new challanges and adventures. "
                   "For even in the darkest of moments, the light of hope shines ever brighter, guiding you towards a new dawn.";
    }
    else if (calculatedScore > 40 && calculatedScore <= 50){

        feedback = "Your journey has been arduous and fraught with peril, but do not lose heart. The path to the Emerald Cipher is not an easy one, "
                   "and many before you have fallen short. Take this opportunity to reflect on your strengths and weaknesses, "
                   "and learn from your mistakes. With renewed vigor and a steadfast spirit, "
                   "you may yet find a way to unravel the mysteries of the past.";
    }
    else if (calculatedScore > 50 && calculatedScore <= 70){

        feedback = "You have proven yourself a worthy opponent, if not a champion, int the quest for the Emerald Cipher. "
                   "Though you have not yet reached the pinnacle of success, the spirits of success, the spirits of Glenhaven recognize your potential and offer you their blessing. "
                   "Take this as a sign of encouragement and continue to hone your skills. "
                   "For the secrets of the Emerald Cipher may yet be revealed to you.";
    }
    else if (calculatedScore > 70 && calculatedScore <= 80){

        feedback = "Well done, brave traveler! Though the mysteries of the Emerald Cipher still elude you, "
                   "your courage and wisdom have earned you a measure of power and respect within the village of Glenhaven. "
                   "The spirits of the past are watching, and they are pleased with your progress. "
                   "Continue on your journey, and you may yet uncover the secrets of the Emerald Cipher.";
    }
    else if (calculatedScore >80 && calculatedScore <= 90){

        feedback = "Congratulations, adventurer! You have succeeded where others have failed, unraveling the cryptic messages and solving "
                   "the mystery of the Emerald Cipher. The ancient spirits of Glenhaven are impressed by your tenacity and prowess, "
                   "and have granted you the key to unlocking their secrets.";
    }
    else {

        feedback = "Bravo! Espionage master. You have succeeded where others have failed, unraveling the cryptic messages and solving the mystery of the Emerald Cipher. "
                   "The ancient spirits of Glenhaven are impressed by your tenacity and prowess, and have granted you the key to unlocking their secrets. "
                   "With this power in your hands, you can now command the powers of the Emerald Cipher, "
                   "restoring prosperity and peace to the village and earning the respect and admiration of its people.";
    }

    feedbackTextEdit = new QTextEdit(this);
    feedbackTextEdit->setText(feedback);
    feedbackTextEdit->setStyleSheet("color: white; font-weight: bold; font-style: italic; font-size: 25px; border: 4px solid green; background-color: transparent;");

    //calculate position for QTextEdit
    int textEditWidth = width() - 300;
    int textEditHeight = 250;
    int textEditX = (width() - textEditWidth) / 4 + 50;
    int textEditY = 250;

    feedbackTextEdit->setGeometry(textEditX, textEditY, textEditWidth, textEditHeight);
    feedbackTextEdit->setAlignment(Qt::AlignCenter);
    feedbackTextEdit->setFrameStyle(QFrame::Panel | QFrame:: Sunken); //add border to the text edit
    feedbackTextEdit->setReadOnly(true);
    feedbackTextEdit->setVisible(true);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::createBorder(QPushButton* button) {
    QString styleSheet = "QPushButton {"
                         "    border: 3px solid green;" // Increased border thickness
                         "    border-radius: 10px;"
                         "    background-color: grey;"
                         "    color: black;" // Set text color to black
                         "}"
                         "QPushButton::hover {"
                         "    border: 10px solid darkGreen;" // Increased border thickness on hover
                         "}";
    button->setStyleSheet(styleSheet);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::updateTimer(Level level) {
    // Set total time based on the current level
    int totalTimeInSeconds = 0;

    // Initialize timer
    timer = new QTimer(this);

    // Start the timer
    timer->start(1000); // Start the timer with a timeout of 1000 ms (1 second)

    level = getCurrentLevel();

    switch(level) {
    case Level::Easy:
        totalTimeInSeconds = 20 * 60; // 20 minutes
        break;
    case Level::Medium:
        totalTimeInSeconds = 15 * 60; // 15 minutes
        break;
    case Level::Hard:
        totalTimeInSeconds = 10 * 60; // 10 minutes
        break;
    default:
        totalTimeInSeconds = 20 * 60; // Default to Easy level
        break;
    }

    // Initialize remaining time to total time
    int remainingTimeInSeconds = totalTimeInSeconds;

    // Create ring progress bar and start with full value
    progressBar->setValue(0); // Start with 0%

    connect(timer, &QTimer::timeout, [=]() mutable {
        // Update the timer label text
        QString timeString = QTime(0, 0).addSecs(remainingTimeInSeconds).toString("mm:ss");
        timerLabel->setText(timeString);

        // Decrease the remaining time
        remainingTimeInSeconds--;

        // Calculate the progress based on the remaining time and total time
        int progress = 100 - ((remainingTimeInSeconds * 100) / totalTimeInSeconds);

        // Update the progress bar value
        progressBar->setValue(progress);

        // Change progress bar color when reaching half time and 30 seconds left
        if (remainingTimeInSeconds <= totalTimeInSeconds/2) {
            progressBar->setProgressColor(QColorConstants::Svg::orange);
        }

        if (remainingTimeInSeconds <= 60) {
            progressBar->setProgressColor(Qt::red);
        }

        // Check if the timer has reached 00:00
        if (remainingTimeInSeconds < 0) {
            // Stop the timer
            timer->stop();

            // Set progress bar to 0
            progressBar->setValue(100);
            // Show feedback window
            showFeedbackWindow();
        }
    });
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_easyButton_clicked()
{
    // Check if an animation is already in progress
    if (!animationInProgress) {
        // If no animation is in progress, start the fadeOut animation
        fadeOutWidget(ui->tabWidget);
    }

    if (buttonSoundsEnabled){
        playClickSound();
    }else{
        stopClickSound();
    }

    hintNum = 4;
    numSkip = 6;
    // Set current level to Easy
    currentLevel = Level::Easy;
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_mediumButton_clicked()
{
    // Check if an animation is already in progress
    if (!animationInProgress) {
        // If no animation is in progress, start the fadeOut animation
        fadeOutWidget(ui->tabWidget);
    }

    if (buttonSoundsEnabled){
        playClickSound();
    }else{
        stopClickSound();
    }

    hintNum = 2;
    numSkip = 4;
    // Set current level to Easy
    currentLevel = Level::Medium;
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_hardButton_clicked()
{
    // Check if an animation is already in progress
    if (!animationInProgress) {
        // If no animation is in progress, start the fadeOut animation
        fadeOutWidget(ui->tabWidget);
    }

    if (buttonSoundsEnabled){
        playClickSound();
    }else{
        stopClickSound();
    }

    hintNum = 2;
    numSkip = 0;
    // Set current level to Easy
    currentLevel = Level::Hard;
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::answerButton1_OnClick(){
    isSelected = 0;
    disableOptionButtons();
    if (isCorrectAnswer()){
        answerButton1->setStyleSheet("background: green;");
        score ++; //increment points if correct answer is checked
        scoreDisplay->setText(QString::number(score));
        hintButton->setEnabled(false);
        consecutiveCorrectAnswers++;

    }
    else{
        answerButton1->setStyleSheet("background: red;");
        consecutiveCorrectAnswers = 0;
        QString feedback = generateFeedbackMessage();

        QString displayText = feedback + "\n" +
                              currentQuestion.getAnswerOption()[currentQuestion.getCorrectIndex()] +
                              " is the answer you were looking for";

        correctAnswerLabel1->setVisible(true);
        correctAnswerLabel1->setText(displayText);
        correctAnswerLabel1->setStyleSheet("color: white;");

    }if (buttonSoundsEnabled){
        playAnswerSound();
    }else{
        stopAnswerSound();
    }
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::answerButton2_OnClick(){
    isSelected = 1;
    disableOptionButtons();

    if (isCorrectAnswer()){
        answerButton2->setStyleSheet("background: green;");
        score ++; //increment points if correct answer is checked
        consecutiveCorrectAnswers++;
        scoreDisplay->setText(QString::number(score));
        hintButton->setEnabled(false);

    }
    else{
        answerButton2->setStyleSheet("background: red;");
        consecutiveCorrectAnswers = 0;
        QString feedback = generateFeedbackMessage();

        QString displayText = feedback + "\n" +
                              currentQuestion.getAnswerOption()[currentQuestion.getCorrectIndex()] +
                              "\nis the answer you were looking for";

        correctAnswerLabel2->setVisible(true);
        correctAnswerLabel2->setText(displayText);
        correctAnswerLabel2->setStyleSheet("color: white;");


    }if (buttonSoundsEnabled){
        playAnswerSound();
    }else{
        stopAnswerSound();
    }
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::answerButton3_OnClick(){
    isSelected = 2;
    disableOptionButtons();

    disableOptionButtons();
    if (isCorrectAnswer()){
        answerButton3->setStyleSheet("background: green;");
        score ++; //increment points if correct answer is checked
        scoreDisplay->setText(QString::number(score));
        hintButton->setEnabled(false);
        consecutiveCorrectAnswers++;


    }
    else{
        answerButton3->setStyleSheet("background: red;");
        consecutiveCorrectAnswers = 0;

        QString feedback = generateFeedbackMessage();

        QString displayText = feedback + "\n" +
                              currentQuestion.getAnswerOption()[currentQuestion.getCorrectIndex()] +
                              "\nis the answer you were looking for";

        correctAnswerLabel3->setVisible(true);
        correctAnswerLabel3->setText(displayText);
        correctAnswerLabel3->setStyleSheet("color: white;");

    }if (buttonSoundsEnabled){
        playAnswerSound();
    }else{
        stopAnswerSound();
    }
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::answerButton4_OnClick(){
    isSelected = 3;
    disableOptionButtons();

    disableOptionButtons();
    if (isCorrectAnswer()){
        answerButton4->setStyleSheet("background: green;");
        score ++; //increment points if correct answer is checked
        scoreDisplay->setText(QString::number(score));
        hintButton->setEnabled(false);
        consecutiveCorrectAnswers++;

    }else{
        answerButton4->setStyleSheet("background: red;");
        consecutiveCorrectAnswers = 0;
        QString feedback = generateFeedbackMessage();

        QString displayText = feedback + "\n" +
                              currentQuestion.getAnswerOption()[currentQuestion.getCorrectIndex()] +
                              "\nis the answer you were looking for";

        correctAnswerLabel4->setVisible(true);
        correctAnswerLabel4->setText(displayText);
        correctAnswerLabel4->setStyleSheet("color: white;");


    }if (buttonSoundsEnabled){
        playAnswerSound();
    }else{
        stopAnswerSound();
    }
}
//--------------------------------------------------------------------------------------------------------------------------
bool MainWindow::isCorrectAnswer(){
    return (currentQuestion.getAnswerOption() [isSelected] ==
            currentQuestion.getAnswerOption() [currentQuestion.getCorrectIndex()]);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::displayQuestion(){

    currentQuestion = db.generateQuestion();//generate random Question
    const QString questionType = currentQuestion.getQuestionType();
    questionTextEdit->setText(currentQuestion.getQuestion()); // Set text here

    if(questionType == "True/False"){

        answerButton1->setVisible(true);
        answerButton2->setVisible(true);

        answerButton1->setText(currentQuestion.getAnswerOption()[0]);
        answerButton2->setText(currentQuestion.getAnswerOption()[1]);

        createBorder(answerButton1);
        createBorder(answerButton2);

        // Hide the last two buttons
        answerButton3->setVisible(false);
        answerButton4->setVisible(false);

        // Hide the last two circles
        optionCircleC->setVisible(false);
        optionCircleD->setVisible(false);
    }
    else if(questionType == "MCQ"){
        questionTextEdit->toPlainText();
        answerButton1->setText(currentQuestion.getAnswerOption()[0]);
        answerButton2->setText(currentQuestion.getAnswerOption()[1]);
        answerButton3->setText(currentQuestion.getAnswerOption()[2]);
        answerButton4->setText(currentQuestion.getAnswerOption()[3]);

        createBorder(answerButton1);
        createBorder(answerButton2);
        createBorder(answerButton3);
        createBorder(answerButton4);

        // Show all four buttons
        answerButton1->setVisible(true);
        answerButton2->setVisible(true);
        answerButton3->setVisible(true);
        answerButton4->setVisible(true);

        // Show all four circles
        optionCircleA->setVisible(true);
        optionCircleB->setVisible(true);
        optionCircleC->setVisible(true);
        optionCircleD->setVisible(true);
    }
    if(!db.getQuestionList().empty()){
        db.removeQuestion(currentQuestion);
    }
    enableOptionButtons();
    hideCorrectAnswerLabel();
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::nextBtnOnClick(){

    if(consecutiveCorrectAnswers >= 3 && maxQuestions < 9){
        //If the player has answered three consecutive questions correctly, show the help button
        showHelpButton();
    }

    if ((db.getQuestionList().size()>1)){

        if (maxQuestions < 9 ){
            displayQuestion();
            enableOptionButtons();
            toggleButtonSounds(nextButton);
            maxQuestions ++;

        }else {

        nextButton->setVisible(false);
        submit->setVisible(true);
        }
    }
     else{
        db.loadQuestion();
        displayQuestion();
    }
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_skipBtn_clicked(){
    if ((db.getQuestionList().size()>1)){
        if (numSkip > 0) {
            displayQuestion(); //display next question
            enableOptionButtons();
            numSkip --;
            skipLabel->setText(QString::number(numSkip));
        }else {
             skipButton->setEnabled(false);
        }
         setDefaultColor();
    }
    else{
        db.loadQuestion();
        displayQuestion();
    }
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::disableOptionButtons(){

    answerButton1->setEnabled(false);
    answerButton2->setEnabled(false);
    answerButton3->setEnabled(false);
    answerButton4->setEnabled(false);

    skipButton->setEnabled(false);
    nextButton->setEnabled(true);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::enableOptionButtons(){

    answerButton1->setEnabled(true);
    answerButton2->setEnabled(true);
    answerButton3->setEnabled(true);
    answerButton4->setEnabled(true);

    skipButton->setEnabled(true);
    nextButton->setEnabled(false);
    hintButton->setEnabled(true);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_hintBtn_clicked(){

    if (hintNum > 0) {
        hintNum--;
        hintLabel->setText(QString::number(hintNum));
        hintMessage->setText(currentQuestion.getHint());
        hintMessage->exec(); // Display the message box
    } else {
        hintButton->setEnabled(false);
    }
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::playBackgroundMusic()
{
    // Load the background music from the resource file
    if (!backgroundMusic.openFromFile("/home/aphiwe/Downloads/Quiz_game_project/espoQuest/pictures/background_music.wav")) {
        qDebug() << "Error loading music";
        return; // Exit the method if loading fails
    }

    // Set the volume
    backgroundMusic.setVolume(20); // Adjust volume as needed

    // Set whether the music should loop
    backgroundMusic.setLoop(true); // Loop indefinitely

    // Play the background music
    backgroundMusic.play();
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::playClickSound(){

    // Load the click sound from the resource file
    if (!clickBuffer.loadFromFile("/home/aphiwe/Downloads/Quiz_game_project/espoQuest/pictures/click_sound.wav")) {
        qDebug() << "Error loading click sound";
        return; // Exit the method if loading fails
    }

    // Create a sound object and set its buffer to the loaded click sound
    clickSound.setBuffer(clickBuffer);

    // Set the volume
    clickSound.setVolume(60); // Adjust volume as needed

    // Play the click sound
    clickSound.play();
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::updateProgress(){

    // Increase the progress bar value by 10%
    int newValue = progress->value() + 10;
    progress->setValue(newValue);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::playAnswerSound(){

    if (isCorrectAnswer()){
        if (!answerSoundBuffer.loadFromFile("/home/aphiwe/Downloads/Quiz_game_project/espoQuest/pictures/correct_answer.wav")) {
            qDebug() << "Error loading click sound";
            return; // Exit the method if loading fails
        }
    }else {
        if (!answerSoundBuffer.loadFromFile("/home/aphiwe/Downloads/Quiz_game_project/espoQuest/pictures/wrong_answer.wav")) {
            qDebug() << "Error loading click sound";
            return; // Exit the method if loading fails
        }
    }
    // Create a sound object and set its buffer to the loaded click sound
    answerSound.setBuffer(answerSoundBuffer);

    // Set the volume
    answerSound.setVolume(60); // Adjust volume as needed

    // Play the click sound
    answerSound.play();
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_musicButton_clicked()
{
    if (isMusicPlaying) {
        backgroundMusic.stop();
        ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->musicButton->setToolTip(tr("Play Music"));
        isMusicPlaying = false;
    } else {
        backgroundMusic.play();
        ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
        ui->musicButton->setToolTip(tr("Stop Music"));
        isMusicPlaying = true;
    }
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_soundButton_clicked()
{
    // Toggle the state of button sounds
    buttonSoundsEnabled = !buttonSoundsEnabled;

    // Update the icon and tooltip of the soundButton
    QIcon icon;
    QString toolTip;
    if (buttonSoundsEnabled) {
        icon = QIcon::fromTheme("audio-volume-high");
        toolTip = tr("Sound On");
    } else {
        icon = QIcon::fromTheme("audio-volume-muted");
        toolTip = tr("Sound Off");
    }
    ui->soundButton->setIcon(icon);
    ui->soundButton->setToolTip(toolTip);
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::stopClickSound() {
    // Stop the click sound if it is currently playing
    clickSound.stop();
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::stopAnswerSound(){
    answerSound.stop();
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::toggleButtonSounds(QPushButton *button)
{
    if (buttonSoundsEnabled) {
        button->connect(button, &QPushButton::clicked, this, &MainWindow::playClickSound);
    }else{
        button->connect(button, &QPushButton::clicked, this, &MainWindow::stopClickSound);
    }
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::setDefaultColor(){
    answerButton1->setStyleSheet("background: grey");
    answerButton2->setStyleSheet("background: grey");
    answerButton3->setStyleSheet("background: grey");
    answerButton4->setStyleSheet("background: grey");
}
//--------------------------------------------------------------------------------------------------------------------------
void MainWindow::hideQuizWindow(){

    timer->stop(); //stop timer to restart
    maxQuestions = 0; //reset max questions

    //hide all qiuz window widgets
    quizBackground->setVisible(false);
    quizFrame->setVisible(false);
    skipIntroButton->setVisible(false);
    answerButton1->setVisible(false);
    answerButton2->setVisible(false);
    answerButton3->setVisible(false);
    answerButton4->setVisible(false);
    optionCircleA->setVisible(false);
    optionCircleB->setVisible(false);
    optionCircleC->setVisible(false);
    optionCircleD->setVisible(false);
    hintButton->setVisible(false);
    hintLabel->setVisible(false);
    skipButton->setVisible(false);
    skipLabel->setVisible(false);
    scoreDisplay->setVisible(false);
    quitQuizButton->setVisible(false);
    scoreLabel->setVisible(false);
    scrollArea->setVisible(false);
    questionTextEdit->setVisible(false);
    timerLabel->setVisible(false);
    progress->setVisible(false);
    nextButton->setVisible(false);
    submit->setVisible(false);
    hideCorrectAnswerLabel();
    progressBar->setVisible(false);

}
//----------------------------------------------------------------------------------------------------------------------
// Define a method to generate random feedback messages
QString MainWindow::generateFeedbackMessage() {
    // List of feedback messages with corresponding emojis
    QMap<QString, QString> feedbackMessages;

    feedbackMessages["Oh no, that wasn't quite right! But don't worry, spies stumble too."] = "😕";
    feedbackMessages["Close, but not quite. Keep your wits about you!"] = "🤔";
    feedbackMessages["That answer may have been a decoy. Let's try again!"] = "🔍";
    feedbackMessages["Hmm, that answer seems to be encrypted. Keep deciphering!"] = "🔒";
    feedbackMessages["Not quite the right combination. Keep exploring for clues!"] = "🔍";
    feedbackMessages["Almost there, but the final piece of the puzzle eludes you!"] = "🧩";
    feedbackMessages["Not the answer we were hoping for. Let's try another approach!"] = "😔";
    feedbackMessages["A valiant effort, but the true solution remains hidden."] = "💪";
    feedbackMessages["Your intuition is commendable, but the answer lies deeper."] = "🤔";
    feedbackMessages["An intriguing guess, but the mystery remains unsolved."] = "🕵";
    feedbackMessages["A worthy attempt, but the secrets of the cipher remain veiled."] = "🔒";
    feedbackMessages["A clever deduction, but the true path lies beyond."] = "🤓";
    feedbackMessages["The trail grows colder, but your determination shines through."] = "🔍";

    // Select a random feedback message from the list
    int index = std::rand() % feedbackMessages.size();
    return feedbackMessages.keys().at(index) + " " + feedbackMessages.values().at(index);
}
//----------------------------------------------------------------------------------------------------------------------
void MainWindow::hideFeedBackWindow(){

    feedbackBackground->setVisible(false);
    feedbackFrame->setVisible(false);
    backButton->setVisible(false);
    retryBtn->setVisible(false);
    retryLabel->setVisible(false);
    finalScoreLabel->setVisible(false);
    submit->setVisible(false);
    feedbackTextEdit->setVisible(false);
    hideCorrectAnswerLabel();

}
//----------------------------------------------------------------------------------------------------------------------
void MainWindow::hideCorrectAnswerLabel() {
    correctAnswerLabel1->setVisible(false);
    correctAnswerLabel2->setVisible(false);
    correctAnswerLabel3->setVisible(false);
    correctAnswerLabel4->setVisible(false);

}
//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_retryButton_clicked(){

    finalScoreLabel->setText("");

    switch(currentLevel){
    case Level::Easy:
        numSkip = 6;
        hintNum = 4;
        break;
    case Level::Medium:
        numSkip = 4;
        hintNum = 2;
        break;
    case Level::Hard:
        numSkip = 2;
        hintNum = 0;
        break;
    default:
        break;

    }
    showQuizWindow();
}
//----------------------------------------------------------------------------------------------------------------------
void MainWindow::showCorrectAnswer(){
    if(isCorrectAnswer()){

    }
}
//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_quitBtn_clicked()
{
    this->close();
}

