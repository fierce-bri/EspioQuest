#include "question.h"

// Constructor for Question class
Question::Question() {}
Question::~Question(){}

// Parameterized constructor for Question class
Question::Question(const QString question, std::initializer_list<QString> answerOptions, const QString hint, int isCorrectIndex, const QString questionType){
    // Initialize member variables with provided values
    this->question = question;
    this->answerOptions = answerOptions;
    this->isCorrectIndex = isCorrectIndex;
    this->hint = hint;
    this->questionType = questionType;
}

//getter methods for retrieval
QString Question::getQuestion(){
    return question;
}
QString Question::getHint(){
    return hint;
}
int Question::getCorrectIndex(){
    return isCorrectIndex;
}
QVector<QString>Question::getAnswerOption(){
    return answerOptions;
}

QString Question::getQuestionType(){
    return questionType;
}

// Overloaded equality operator for Question class
bool Question::operator==(const Question& other) const {
    // Compare relevant fields for equality
    return (question == other.question &&
            answerOptions == other.answerOptions &&
            hint == other.hint &&
            questionType == other.questionType &&
            isCorrectIndex == other.isCorrectIndex);
}
