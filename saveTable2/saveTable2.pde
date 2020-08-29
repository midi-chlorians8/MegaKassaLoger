// Очистка таблици пока вручную
// Не удалять первые строки в таблице
Table table;
String Example = "2 12.08.20 14.13.11 F";
void setup() {

  //table = new Table();
  table = loadTable("new.csv", "header");
  println(table.getRowCount() + " total rows in table");

  //table.addColumn("id");
  //table.addColumn("Received");
  //table.addColumn("name");
  /*
  TableRow newRow = table.addRow();
  newRow.setInt("id", table.getRowCount() - 1);
  newRow.setString("species", "Panthera leo");
  newRow.setString("name", "Lion");
  */
  /*
  table.addRow (); // Создает новую пустую строку
  newRow.setInt("id", table.getRowCount() - 1);
  newRow.setString("species", "Panthera leo");
  newRow.setString("name", "Lion");
  */
  
 // saveTable(table, "data/new.csv");
 
}
void draw(){
  TableRow newRow = table.addRow();
  newRow.setInt("id", table.getRowCount() - 1);
  newRow.setString("Received", Example);
  //newRow.setString("name", "Lion");
  saveTable(table, "data/new.csv");
}
// Sketch saves the following to a file called "new.csv":
// id,species,name
// 0,Panthera leo,Lion
