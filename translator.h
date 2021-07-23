#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QMap>

enum Mode
{
    MODE_FROM_MORSE_INTO_ENGLISH,
    MODE_FROM_ENGLISH_INTO_MORSE
};

enum Language
{
    LANGUAGE_ENGLISH,
    LANGUAGE_MORSE
};

class Translator : public QObject
{
    Q_OBJECT

public:
    Translator(QObject *parent = 0);

    /**
    *  Parse text into text_ and normalize it.
    */
    Q_INVOKABLE void parseText(QString &text);

    /**
    *  Swap currentMode_ from MODE_FROM_MORSE_INTO_ENGLISH
    *  to MODE_FROM_ENGLISH_INTO_MORSE and vice versa
    */
    Q_INVOKABLE void changeCurrentMode();

    /**
    *  Translate text_ variable.
    */
    Q_INVOKABLE QString translateText();

    /**
    *  Get language of text_ variable.
    */
    Q_INVOKABLE Language getTextLanguage();

    /**
    *  Guess what language presented in text.
    *  Try both of translation modes.
    *  If both of modes returned error there is an error but we return English.
    *  If we can translate text only into English it's Morse text.
    *  If we can translate text only into Morse it's English text.
    *  If we can translate text into both languages it's Morse text.
    */
    Q_INVOKABLE Language guessLanguage(QString &text);

    Q_INVOKABLE const QString getErrorMessage();

private:

    const QList<QString> ENGLISH_CHARACTERS{"a", "b", "c", "d", "e",
                                            "f", "g", "h", "i", "j",
                                            "k", "l", "m", "n", "o",
                                            "p", "q", "r", "s", "t",
                                            "u", "v", "w", "x", "y",
                                            "z"};

    const QList<QString> MORSE_CHARACTERS{".-", "-...", "-.-.", "-..",
                                          ".", "..-.", "--.", "....",
                                         "..", ".---", "-.-", ".-..",
                                         "--", "-.", "---", ".--.",
                                         "--.-", ".-.", "...", "-",
                                         "..-", "...-", ".--", "-..-",
                                         "-.--", "--.."};

    const QString ERROR_MESSAGE = "Ooops. Something goes wrong.";

    Mode currentMode_;
    QString text_;

    /**
    *  Skip forbidden characters.
    *  For English we shouldn't skip only letters and spaces.
    *  For both languages &bsol;n is space.
    */
    QString normalizeText(QString &text, Language textLanguage);

    /**
     *  Translate given text with translationMode.
    */
    QString translateText(QString &text, Mode translationMode);

    /**
     *  Translate single character with translationMode.
    */
    QString translateCharacter(QString &character, Mode translationMode);
};

#endif // TRANSLATOR_H
