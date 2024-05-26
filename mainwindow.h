#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <question.h>
#include "ringprogressbar.h"
#include <questionbank.h>
#include <feedback.h>

#include <QTabWidget>
#include <SFML/Graphics.hpp>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include <QFrame>
#include <QTextEdit>
#include <QDateTime>
#include <QProgressBar>
#include <string>
#include <QMessageBox>
#include <QTimer>
#include <QStyle>
#include <SFML/Audio.hpp>
#include <QAbstractAnimation>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMovie>
#include <QTextEdit>
#include <cstdlib>
#include <QVector>

class QuizWindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Define an enum for the levels
enum Level {
    Easy,
    Medium,
    Hard
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Method to show quiz window
    void showQuizWindow();
    void showFeedbackWindow();

private slots:

    void on_easyButton_clicked();

    void on_mediumButton_clicked();

    void on_hardButton_clicked();

    void on_musicButton_clicked();

    void on_soundButton_clicked();

    void updateTimer(Level level);

    void nextBtnOnClick();

    void answerButton1_OnClick();

    void answerButton2_OnClick();

    void answerButton3_OnClick();

    void answerButton4_OnClick();

    void on_skipBtn_clicked();

    void on_hintBtn_clicked();

    void updateProgress();

    void on_quitBtn_clicked();

    void on_retryButton_clicked();

    void unlockHelp();

public slots:

    void showHelpButton();

private:
    Ui::MainWindow *ui;
    QPushButton *skipIntroButton; // Declare a pointer to QPushButton
    Level currentLevel; // Member variable to store the current level
    int index = 0; // Declare index as an integer member variable

    QFrame *overlay;
    QTextEdit* introductionText;
    QLabel *backgroundLabel;
    QTimer* textTimer;
    QMessageBox* hintMessage;
    int score;
    int isSelected;
    int numSkip;
    int hintNum;
    int maxQuestions;
    double calculatedScore;
    // Define a flag to track whether an animation is in progress
    bool animationInProgress;

    Question currentQuestion;
    QuestionBank db;
    Feedback<double> finalScore;

    QFrame *quizFrame;
    QPushButton *hintButton;
    QPushButton *quitQuizButton;
    QPushButton *nextButton;

    QPushButton *skipButton;
    QLabel *hintLabel;
    QLabel *skipLabel;
    QLabel *scoreLabel;

    QTextEdit *feedbackTextEdit;

    QLabel *correctAnswerLabel1;
    QLabel *correctAnswerLabel2;
    QLabel *correctAnswerLabel3;
    QLabel *correctAnswerLabel4;
    QPropertyAnimation *blinkAnimation;
    QWidget *overlayWidget;
    QLabel *promptLabel;

    int consecutiveCorrectAnswers;
    QPushButton *helpButton;
    bool helpButtonVisible;

    QScrollArea *scrollArea;
    QTextEdit *questionTextEdit;
    QLabel *scoreDisplay;
    QLabel *timerLabel;
    RingProgressBar *progressBar; // Declare a RingProgressBar member variable
    QTimer *timer;
    QLabel *quizBackground;
    QProgressBar *progress;

    int progressBarDiameter;

    sf::RenderWindow m_sfmlWindow;// Declare sf::RenderWindow member variable
    sf::Music backgroundMusic;
    sf::Sound clickSound;
    sf::SoundBuffer clickBuffer;
    sf::Sound answerSound;
    sf::SoundBuffer answerSoundBuffer;
    bool isMusicPlaying = false; // Track the state of background music
    bool buttonSoundsEnabled = true;

    QPushButton* answerButton1;
    QPushButton* answerButton2;
    QPushButton* answerButton3;
    QPushButton* answerButton4;

    QLabel* optionCircleA;
    QLabel* optionCircleB;
    QLabel* optionCircleC;
    QLabel* optionCircleD;

    QLabel* answer;
    QLabel* answerLabel;
    QLabel *finalScoreLabel;
    QLabel *feedbackBackground;
    QFrame *feedbackFrame;

    QLabel* retryLabel;
    QPushButton* retryBtn;
    QPushButton* submit;
    QPushButton* backButton;

    void fadeOutWidget(QTabWidget *tab);
    void fadeInWidget();
    void generateIntroductionText();
    Level getCurrentLevel();
    void displayQuestion();
    void enableOptionButtons();
    void disableOptionButtons();
    void setDefaultColor();
    QString generateFeedbackMessage();

    void createBorder(QPushButton* button);
    void updateButtons(const QString questionType);
    bool isCorrectAnswer();
    void playBackgroundMusic();
    void playClickSound();
    void playAnswerSound();

    void stopClickSound();
    void stopAnswerSound();
    void toggleButtonSounds(QPushButton *button);
    void hideQuizWindow();
    void hideFeedBackWindow();
    void setCorrectLabelDefaultColor();
    void hideCorrectAnswerLabel();
    void showCorrectAnswer();
    void cleanupFeedbackWindow();
    void eliminateChoices();
    void showHintDisplay();
};
#endif // MAINWINDOW_H
