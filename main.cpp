#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>

#include <plugin/redmine/RedmineApi.h>

#include <AppController.h>

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<AppController>("com.AppController", 1, 0, "AppController");

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/view/main.qml")));

	//TODO use signals instead ?
	//	QQuickView view(QUrl(QStringLiteral("qrc:/view/main.qml")));
	//	auto window = view.rootObject();
	//	auto appController = window->findChild("appController");
	//QObject::connect(item, SIGNAL(qmlSignal(QString)), &myClass, SLOT(cppSlot(QString)));
	//	view.show();

	return app.exec();
}

int mainTest()
{
	std::cout << "Hello, World!" << std::endl;

	return 0;
}
