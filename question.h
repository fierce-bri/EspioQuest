#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QVector>

struct Question{
private:
    QString question;
    QString hint;
    QVector<QString> answerOptions;
    int isCorrectIndex;
    QString questionType;
public:
    Question(); //default constructor
    ~Question();
    Question(const QString question, std::initializer_list<QString> answerOptions, const QString hint, int isCorrectIndex, const QString type);

    QString getQuestion();
    QString getHint();
    int getCorrectIndex();
    QVector<QString> getAnswerOption();
    QString getQuestionType();
    bool operator==(const Question& other) const;
};

#endif // QUESTION_H
