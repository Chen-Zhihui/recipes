
··· C++
void WebView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = page()->createStandardContextMenu();
    const QList<QAction*> actions = menu->actions();
    auto it = std::find(actions.cbegin(), actions.cend(), page()->action(QWebEnginePage::OpenLinkInThisWindow));
    if (it != actions.cend()) {
        (*it)->setText(tr("Open Link in This Tab"));
        ++it;
        QAction *before(it == actions.cend() ? nullptr : *it);
        menu->insertAction(before, page()->action(QWebEnginePage::OpenLinkInNewWindow));
        menu->insertAction(before, page()->action(QWebEnginePage::OpenLinkInNewTab));
    }
    connect(menu, &QMenu::aboutToHide, menu, &QObject::deleteLater);
    menu->popup(event->globalPos());
}
···