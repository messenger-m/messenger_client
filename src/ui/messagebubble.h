#ifndef MESSAGEBUBBLE_H
#define MESSAGEBUBBLE_H

#include <QWidget>

class MessageBubble : public QWidget
{
public:
    MessageBubble(QString text, bool isMe);
};

#endif // MESSAGEBUBBLE_H
