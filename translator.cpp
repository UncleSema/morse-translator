#include "translator.h"

Translator::Translator(QObject *parent)
{
    Q_UNUSED(parent)
    text_ = "";
    currentMode_ = MODE_FROM_ENGLISH_INTO_MORSE;
}

void Translator::parseText(QString &text)
{
    text_ = normalizeText(text, getTextLanguage());
}

QString Translator::translateCharacter(QString &character,Mode translationMode)
{
    if (translationMode == MODE_FROM_ENGLISH_INTO_MORSE) {
        for (int i = 0; i<ENGLISH_CHARACTERS.size(); i++) {
            if (ENGLISH_CHARACTERS[i] == character)
                return MORSE_CHARACTERS[i];
        }
    } else {
        for (int i = 0; i<MORSE_CHARACTERS.size(); i++) {
            if (MORSE_CHARACTERS[i] == character)
                return ENGLISH_CHARACTERS[i];
        }
    }
    return getErrorMessage();
}

Language Translator::getTextLanguage()
{
    Language currentLanguage;

    if (currentMode_ == MODE_FROM_ENGLISH_INTO_MORSE)
        currentLanguage = LANGUAGE_ENGLISH;
     else
        currentLanguage = LANGUAGE_MORSE;

    return currentLanguage;
}

QString Translator::normalizeText(QString &text, Language textLanguage)
{
    QString newText = "";

    if (textLanguage == LANGUAGE_ENGLISH) {
        for (QChar &c : text) {
            if (c == '\n') {     // We should replace "\n" with " ".
                newText += " ";
                continue;
            }
            if (c.isLetter() || c.isSpace())
                newText += c;
        }  
    } else {
        for (QChar &c : text) {
            if (c == '\n') {      // We should replace "\n" with " ".
                newText += "  ";
                continue;
            }
            newText += c;
        }
    }

    newText = newText.toLower();
    return newText;
}

Language Translator::guessLanguage(QString &text)
{
    // Guess English.
    QString englishText = normalizeText(text, LANGUAGE_ENGLISH);
    QString translationIntoMorse = translateText(englishText,
                                                 MODE_FROM_ENGLISH_INTO_MORSE);
    bool canTranslateIntoMorse = (translationIntoMorse != getErrorMessage());

    // Guess Morse.
    QString morseText = normalizeText(text, LANGUAGE_MORSE);
    QString translationIntoEnglish = translateText(morseText,
                                                 MODE_FROM_MORSE_INTO_ENGLISH);
    bool canTranslateIntoEnglish = (translationIntoEnglish !=
                                                            getErrorMessage());
    // Conditions.
    if (canTranslateIntoMorse && canTranslateIntoEnglish)
        return LANGUAGE_MORSE;

    if (canTranslateIntoEnglish)
        return LANGUAGE_MORSE;

    if (canTranslateIntoMorse)
        return LANGUAGE_ENGLISH;

    return LANGUAGE_ENGLISH;

}

QString Translator::translateText(QString &text, Mode translationMode)
{
    QString translation = "";
    if (translationMode == MODE_FROM_ENGLISH_INTO_MORSE) {
        QStringList englishWords = text.split(QString(" "),
                                              Qt::SkipEmptyParts);

        for (QString &word : englishWords) {
            for (QChar &letter : word) {
               QString c = static_cast<QString>(letter);
               bool isError = translateCharacter(c, translationMode) ==
                                                             getErrorMessage();
               if (isError)
                    return getErrorMessage();
               translation += translateCharacter(c, translationMode) + " ";
            }
            translation += " ";
        }
    } else {
        QStringList morseWords = text.split(QString("  "),
                                            Qt::SkipEmptyParts);
        QVector<QStringList> letters;

        for (QString &word : morseWords) {
           letters.append(word.split(QString(" "), Qt::SkipEmptyParts));
        }

        for (QStringList &letter : letters) {
            for (QString &c : letter) {
               bool isError = translateCharacter(c, translationMode) ==
                                                             getErrorMessage();
               if (isError)
                    return getErrorMessage();
               translation += translateCharacter(c, translationMode);
            }
            translation += " ";
        }
    }
    // We added space in the end of the string so we should erase it.
    translation.erase(translation.end()-1, translation.end());
    return translation;
}

void Translator::changeCurrentMode()
{
    if (currentMode_ == MODE_FROM_ENGLISH_INTO_MORSE)
        currentMode_ = MODE_FROM_MORSE_INTO_ENGLISH;
    else
        currentMode_ = MODE_FROM_ENGLISH_INTO_MORSE;
}

QString Translator::translateText()
{
    return translateText(text_, currentMode_);
}

const QString Translator::getErrorMessage()
{
    return ERROR_MESSAGE;
}
