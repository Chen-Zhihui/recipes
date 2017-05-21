
# web engine
HTML/CSS rendering engine

## QWebChannel or WebChannel
QWebChannel, 把C++的类型暴露给JS,用于直接绘制HTML
qrc:///qtwebchannel/qwebchannel.js

  new QWebChannel(qt.webChannelTransport,
    function(channel) {
      var content = channel.objects.content; // channel.objects
      updateText(content.text);
      content.textChanged.connect(updateText);
    }
  );



QVariant CWizDocumentWebEngine::synchronousRunJavaScript(const QString& strExec)
{
    QVariant returnValue;
    QEventLoop loop;
    qDebug() << "create loop and loop locker before run js : " << strExec;
    page()->runJavaScript(strExec , [&](const QVariant& result) {
        returnValue = result;
        loop.quit();
        qDebug() << "javascript result : " << result;
    });
    qDebug() << "before loop exec";
    loop.exec(QEventLoop::ExcludeUserInputEvents);
    return returnValue;
}  

void CWizDocumentWebEngine::saveAsPDF()
{        //
    page()->runJavaScript("editor.getAllHtml()", [this](const QVariant& html) {
        QString strHtml = html.toString();
        if (strHtml.isEmpty())
            return;

        QString	fileName = QFileDialog::getSaveFileName (this, QString(), QDir::homePath(), tr("PDF Files (*.pdf)"));
        if (!fileName.isEmpty())
        {
            if (::PathFileExists(fileName))
            {
                ::DeleteFile(fileName);
            }

            QTextDocument textDoc;
            textDoc.setHtml(strHtml);
            QPrinter printer;
            QPrinter::Unit marginUnit =  (QPrinter::Unit)m_app.userSettings().printMarginUnit();
            double marginTop = m_app.userSettings().printMarginValue(wizPositionTop);
            double marginBottom = m_app.userSettings().printMarginValue(wizPositionBottom);
            double marginLeft = m_app.userSettings().printMarginValue(wizPositionLeft);
            double marginRight = m_app.userSettings().printMarginValue(wizPositionRight);
            printer.setPageMargins(marginLeft, marginTop, marginRight, marginBottom, marginUnit);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setColorMode(QPrinter::Color);
            printer.setOutputFileName(fileName);
            //
            textDoc.print(&printer);
        }
    });
}

void CWizDocumentWebEngine::dragEnterEvent(QDragEnterEvent *event)
{
    if (!isEditing())
        return;

    int nAccepted = 0;
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> li = event->mimeData()->urls();
        QList<QUrl>::const_iterator it;
        for (it = li.begin(); it != li.end(); it++) {
            QUrl url = *it;
            if (url.toString().startsWith("file:///")) {
                nAccepted++;
            }
        }

        if (nAccepted == li.size()) {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasFormat(WIZNOTE_MIMEFORMAT_DOCUMENTS)) {
        if (!event->mimeData()->data(WIZNOTE_MIMEFORMAT_DOCUMENTS).isEmpty()) {
            setFocus();
            event->acceptProposedAction();
        }
    }
}
