#include <QCoreApplication>

#include <QSqlQuery>
#include <QtConcurrent>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>


void addUser(const QString& name)
{ 
  QSqlQuery query;
  query.prepare("INSERT INTO users (username) VALUES (:name)");
  query.bindValue(":name", name);

  if(query.exec())
  {
      qDebug() << "user added:" << query.lastError() << endl;
  }
  else
  {
       qDebug() << "Error adding user:" << query.lastError() << endl;
  }
}


void listUsers()
{
  QSqlQuery query("SELECT * FROM users");
  int nameIdx = query.record().indexOf("username");

  while (query.next())
  {
     QString name = query.value(nameIdx).toString();
     qDebug() << "users:" << name << endl;
  }
}


void dbTest()
{
  QSqlDatabase db;
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("./users.db");

  if (db.open())
  {
    qDebug()<< "Connection Ok!" << endl;
  }
  else
  {
    qDebug() << "Connection Error:" << db.lastError().text() << endl;
  }

  addUser("testuser1");
  addUser("testuser2");

  listUsers();
}


int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  dbTest();

  return a.exec();
}


