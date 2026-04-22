#include "messagebubble.h"
#include <QLabel>
#include <QHBoxLayout>

MessageBubble::MessageBubble(QString text, bool isMe)
{
    QLabel* label = new QLabel(text);
    label->setWordWrap(true);

    if(isMe)
    {
        label->setStyleSheet(R"(
            background:#3b82f6;
            color:white;
            border-radius:10px;
            padding:8px;
        )");
    }
    else
    {
        label->setStyleSheet(R"(
            background:#334155;
            color:white;
            border-radius:10px;
            padding:8px;
        )");
    }

    QHBoxLayout* layout = new QHBoxLayout(this);

    if(isMe)
    {
        layout->addStretch();
        layout->addWidget(label);
    }
    else
    {
        layout->addWidget(label);
        layout->addStretch();
    }
}
