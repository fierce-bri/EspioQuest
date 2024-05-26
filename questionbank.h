#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H

#include "question.h"
#include <QList>

class QuestionBank
{
private:
    QList<Question> questions;
public:
    QuestionBank();
    QList<Question> getQuestionList();
    QList<Question> loadQuestion();
    Question generateQuestion();
    void removeQuestion(const Question& question);
    int maxQuestions = 10; // Variable to store the maximum number of questions, default is 10
};

#endif // QUESTIONBANK_H
