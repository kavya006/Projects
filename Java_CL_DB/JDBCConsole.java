import java.sql.*;
import java.util.Scanner;

public class JDBCConsole {
   // JDBC driver name and database URL
   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
   static final String DB_URL = "jdbc:mysql://localhost/assign";

   //  Database credentials
   static final String USER = "kavya";
   static final String PASS = "kavya006";
   
   public static void main(String[] args) {
	   Connection conn = null;
	   Statement stmt = null;
	   Scanner in = new Scanner(System.in);
	   try{
	      Class.forName("com.mysql.jdbc.Driver");
	      conn = DriverManager.getConnection(DB_URL,USER,PASS);
	      DatabaseMetaData md = conn.getMetaData();
	      String[] types = {"TABLE"};
	      ResultSet tables = md.getTables(null, null, "%", types);
	      while(true){
	    	  System.out.println("Choose an option");
	    	  System.out.println("1 : ADD a row to a table");
	    	  System.out.println("2: DELETE a row from a table");
	    	  System.out.println("3: UPDATE or MODIFY certain values in a table");
	    	  System.out.println("4: DISPLAY the contents of a table");
	    	  System.out.println("5: EXIT");
	    	  System.out.print("Your Choice: ");
	    	  int option = in.nextInt();
	    	  String [] values;
	    	  switch(option){
	    	  	case 1:
	    	  		int i = 1;
	    	  		System.out.println("Choose to table to perform INSERT");
	    	  		while(tables.next()){
	    	  			System.out.println(i++ + ": " + tables.getString(3));
	    	  		}
	    	  		System.out.print("Your choice: ");
	    	  		int rowopt = in.nextInt();
	    	  		tables.absolute(rowopt);
	    	  		System.out.println("Give the values which you want to add");
	    	  		ResultSet columns = md.getColumns(null, null, tables.getString(3), null);
	    	  		i = 1;
	    	  		String sql = "INSERT INTO " + tables.getString(3) + "(";
	    	  		int columnCount = 0;
	    	  		if(columns.last()){
	    	  			columnCount = columns.getRow();
	    	  			columns.beforeFirst();
	    	  		}
	    	  		String value = "";
//	    	  		String[] values = new String[columnCount];
	    	  		in.useDelimiter("\n");
	    	  		while(columns.next()){
	    	  			System.out.print(i + ": " + columns.getString(4) + ": ");
	    	  			sql += columns.getString(4);
	    	  			String a = in.next();
	    	  			if(!a.equals("")){
		    	  			if(columns.getInt(5) >= 11){
		    	  				a = "\"" + a + "\"";
		    	  			}
	    	  			}else{
	    	  				a = "NULL";
	    	  			}
		    	  			value += a;
	    	  			if(i != columnCount){
	    	  				sql += ", ";
	    	  				value += ", ";
	    	  			}
	    	  			i++;
	    	  		}
	    	  		sql += ") VALUES (" + value + ");";
	    	  		System.out.println(sql);
	    	  		stmt = conn.createStatement();
	    	  		stmt.execute(sql);
	    	  		in.reset();
	    	  		tables.beforeFirst();
	    	  		break;
	    	  	case 2:
	    	  		i = 1;
	    	  		System.out.println("Choose to table to perform DELETE");
	    	  		while(tables.next()){
	    	  			System.out.println(i++ + ": " + tables.getString(3));
	    	  		}
	    	  		System.out.print("Your choice: ");
	    	  		rowopt = in.nextInt();
	    	  		tables.absolute(rowopt);
	    	  		System.out.println("Give the parameters to identify the row you want to delete");
	    	  		columns = md.getColumns(null, null, tables.getString(3), null);
	    	  		i = 1;
	    	  		sql = "DELETE FROM " + tables.getString(3);
	    	  		columnCount = 0;
	    	  		if(columns.last()){
	    	  			columnCount = columns.getRow();
	    	  			columns.beforeFirst();
	    	  		}
	    	  		in.useDelimiter("\n");
	    	  		values = new String[columnCount];
	    	  		while(columns.next()){
	    	  			System.out.print(i + ": " + columns.getString(4) + ": ");
	    	  			String a = in.next();
//	    	  			System.out.println(columns.getString(6));
	    	  			if(!a.equals("")){
		    	  			if(columns.getInt(5) >= 11){
		    	  				a = "\"" + a + "\"";
		    	  			}
		    	  			values[i-1] = columns.getString(4) + " = " + a;
	    	  			}else{
	    	  				values[i-1] = null;
	    	  			}
	    	  			i++;
	    	  		}
	    	  		String whereClause = "";
	    	  		for(int j = 0;j < columnCount;j++){
	    	  			if(values[j] == null)
	    	  				continue;
	    	  			if(!whereClause.equals(""))
	    	  				whereClause+= ", ";
	    	  			whereClause += values[j];
	    	  		}
	    	  		if(!whereClause.equals(""))
	    	  			sql += " where " + whereClause;
	    	  		sql += ";";
	    	  		System.out.println(sql);
	    	  		stmt = conn.createStatement();
	    	  		stmt.execute(sql);
	    	  		in.reset();
	    	  		tables.beforeFirst();
	    	  		break;
	    	  	case 3:
	    	  		i = 1;
	    	  		System.out.println("Choose to table to UPDATE / MODIFY");
	    	  		while(tables.next()){
	    	  			System.out.println(i++ + ": " + tables.getString(3));
	    	  		}
	    	  		System.out.print("Your choice: ");
	    	  		rowopt = in.nextInt();
	    	  		tables.absolute(rowopt);
	    	  		System.out.println("Give the new values to modify the row(s)");
	    	  		columns = md.getColumns(null, null, tables.getString(3), null);
	    	  		i = 1;
	    	  		sql = "UPDATE " + tables.getString(3);
	    	  		columnCount = 0;
	    	  		if(columns.last()){
	    	  			columnCount = columns.getRow();
	    	  			columns.beforeFirst();
	    	  		}
	    	  		in.useDelimiter("\n");
	    	  		int count = columnCount;
	    	  		values = new String[columnCount];
	    	  		for(int j = 0;j < columnCount;j++){
	    	  			values[j] = "";
	    	  		}
	    	  		while(columns.next()){
	    	  			System.out.print(i + ": " + columns.getString(4) + ": ");
	    	  			String a = in.next();
//	    	  			System.out.println(columns.getString(6));
	    	  			if(!a.equals("")){
		    	  			if(columns.getInt(5) >= 11){
		    	  				a = "\"" + a + "\"";
		    	  			}
		    	  			values[i-1] = columns.getString(4) + " = " + a;
	    	  			}
	    	  			else 
	    	  				values[i-1] = null;
	    	  			i++;
	    	  		}
	    	  		String setClause = "";
	    	  		for(int j = 0;j < columnCount;j++){
	    	  			if(values[j] == null)
	    	  				continue;
	    	  			if(!setClause.equals(""))
	    	  				setClause += ", ";
	    	  			setClause += values[j];
	    	  		}
	    	  		if(!setClause.equals("")){
	    	  			sql += " SET " + setClause;
	    	  		}
	    	  		whereClause = "";
	    	  		columns.beforeFirst();
	    	  		i = 1;
	    	  		columnCount = count;
	    	  		System.out.println("Subject to the conditions: ");
	    	  		while(columns.next()){
	    	  			System.out.print(i + ": " + columns.getString(4) + ": ");
	    	  			String a = in.next();
//	    	  			System.out.println(columns.getString(6));
	    	  			if(!a.equals("")){
		    	  			if(columns.getInt(5) >= 11){
		    	  				a = "\"" + a + "\"";
		    	  			}
		    	  			values[i-1] = columns.getString(4) + " = " + a;
	    	  			}else{
	    	  				values[i-1] = null;
	    	  			}
	    	  			i++;
	    	  		}
	    	  		for(int j = 0;j < columnCount;j++){
	    	  			if(values[j] == null)
	    	  				continue;
	    	  			if(!whereClause.equals(""))
	    	  				whereClause += ", ";
	    	  			whereClause += values[j];
	    	  		}
	    	  		if(!whereClause.equals("")){
	    	  			sql += " WHERE " + whereClause;
	    	  		}
	    	  		sql += ";";
	    	  		System.out.println(sql);
	    	  		stmt = conn.createStatement();
	    	  		stmt.execute(sql);
	    	  		in.reset();
	    	  		tables.beforeFirst();
	    	  		break;
	    	  	case 4:
	    	  		i = 1;
	    	  		System.out.println("Choose to table to perform SELECT");
	    	  		while(tables.next()){
	    	  			System.out.println(i++ + ": " + tables.getString(3));
	    	  		}
	    	  		System.out.print("Your choice: ");
	    	  		rowopt = in.nextInt();
	    	  		tables.absolute(rowopt);
	    	  		System.out.println("Give the parameters to identify the row you want to see");
	    	  		columns = md.getColumns(null, null, tables.getString(3), null);
	    	  		i = 1;
	    	  		sql = "SELECT ";
	    	  		columnCount = 0;
	    	  		if(columns.last()){
	    	  			columnCount = columns.getRow();
	    	  			columns.beforeFirst();
	    	  		}
	    	  		in.useDelimiter("\n");
	    	  		values = new String[columnCount];
	    	  		for(int j = 0;j < columnCount;j++){
	    	  			values[j] = "";
	    	  		}
	    	  		System.out.println("Do you want to select this column ? If yes, give an alias or leave the field black. Else, give a \"n\"");
	    	  		while(columns.next()){
	    	  			System.out.print(i + ": " + columns.getString(4) + ": ");
	    	  			String a = in.next();
	    	  			if(!a.equals("n")){
	    	  				values[i-1] = "default";
	    	  				if(!a.equals("")){
	    	  					values[i-1] = a;
	    	  				}
	    	  			}else if(a.equals("n")){
	    	  				values[i-1] = null;
	    	  			}
	    	  			i++;
	    	  		}
	    	  		count =0;
	    	  		String fromClause = "";
	    	  		for(int j = 0;j < columnCount;j++){
//	    	  			System.out.println(values[j]);
	    	  			if(values[j] == null)
	    	  				continue;
	    	  			if(!fromClause.equals(""))
	    	  				fromClause += ", ";
	    	  			columns.absolute(j+1);
	    	  			count++;
    	  				fromClause += values[j].equals("default") ? columns.getString(4) : columns.getString(4) + " as " + values[j];
	    	  		}
	    	  		sql += fromClause + " FROM " + tables.getString(3);
	    	  		whereClause = "";
	    	  		columns.beforeFirst();
	    	  		i = 1;
	    	  		System.out.println("Subject to the conditions: ");
	    	  		while(columns.next()){
	    	  			System.out.print(i + ": " + columns.getString(4) + ": ");
	    	  			String a = in.next();
//	    	  			System.out.println(columns.getString(6));
	    	  			if(!a.equals("")){
		    	  			if(columns.getInt(5) >= 11){
		    	  				a = "\"" + a + "\"";
		    	  			}
		    	  			values[i-1] = columns.getString(4) + " = " + a;
	    	  			}else{
	    	  				values[i-1] = null;
	    	  			}
	    	  			i++;
	    	  		}
	    	  		for(int j = 0;j < columnCount;j++){
	    	  			if(values[j] == null)
	    	  				continue;
	    	  			if(!whereClause.equals(""))
	    	  				whereClause += ", ";
	    	  			whereClause += values[j];
	    	  		}
	    	  		if(!whereClause.equals("")){
	    	  			sql += " WHERE " + whereClause;
	    	  		}
	    	  		sql += ";";
	    	  		System.out.println(sql);
	    	  		stmt = conn.createStatement();
	    	  		columns.beforeFirst();
	    	  		ResultSet rs = stmt.executeQuery(sql);
	    	  		int j = 0;
	    	  		for(;j < columnCount;j++){
	    	  			if(values[j] == null)
	    	  				continue;
	    	  			columns.absolute(j+1);
	    	  			System.out.printf("| %10s |", values[j].equals("default") ? columns.getString(4) : values[j]);
	    	  		}
	    	  		System.out.println("\n");
	    	  		i = 1;
	    	  		while(rs.next()){
	    	  			for(i = 1;i <= count;i++)
	    	  				System.out.printf("| %10s |", rs.getString(i));
	    	  			System.out.println("");
	    	  		}
	    	  		
	    	  		in.reset();
	    	  		tables.beforeFirst();
	    	  		break;
	    	  	case 5:
	    	  		break;
	    	  	default:
	    	  		break;
	    	  		
	    	  }
	    	  if(option == 5){
	    		  break;
	    	  }
	    	  System.out.println("\n")	;
	      }
	      System.out.println("");
	      in.close();
	   }catch (ClassNotFoundException e) {
		   e.printStackTrace();
	   }catch (SQLException e) {
		   e.printStackTrace();
	   }finally{
		   
	   }
   }
}