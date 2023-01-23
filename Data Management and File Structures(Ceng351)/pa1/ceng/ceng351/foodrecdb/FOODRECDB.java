package ceng.ceng351.foodrecdb;

import java.sql.*;
import java.util.ArrayList;

public class FOODRECDB implements IFOODRECDB{
    private static String user = "e2448850";
    private static String password = "-4VtWrqweD78aDLp";
    private static String host = "momcorp.ceng.metu.edu.tr";
    private static String database = "db2448850";
    private static int port = 8080;

    private static Connection connection = null;
    @Override
    public void initialize() {
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection =  DriverManager.getConnection(url, user, password);
        }
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public int createTables() {
        int numberOfTables = 0;

        //MenuItems(itemID:int, itemName:varchar(40), cuisine:varchar(20), price:int) itemID p.k
        String queryCreateMenuItemsTable = "create table if not exists MenuItems (" +
                "itemID int ," +
                "itemName varchar(40) ," +
                "cuisine varchar(60) ," +
                "price int ," +
                "primary key (itemID))";

        //Ingredients(ingredientID:int, ingredientName:varchar(40)) ingredientID p.k
        String queryCreateIngredientsTable = "create table if not exists Ingredients (" +
                "ingredientID int ," +
                "ingredientName varchar(40) ," +
                "primary key (ingredientID))";

        //Includes(itemID:int, ingredientID:int) pk(itemID,ingID)
        String queryCreateIncludesTable = "create table if not exists Includes (" +
                "itemID int ," +
                "ingredientID int ," +
                "primary key (itemID,ingredientID) ," +
                "foreign key (itemID) references MenuItems(itemID) on delete cascade on update cascade ," +
                "foreign key (ingredientID) references Ingredients(ingredientID) on delete cascade on update cascade ) ";


        String queryCreateRatingsTable = "create table if not exists Ratings (" +
                "ratingID int ," +
                "itemID int ," +
                "rating int ," +
                "ratingDate date ," +
                "primary key (ratingID) ," +
                "foreign key (itemID) references MenuItems(itemID) on delete cascade on update cascade)";

        String queryCreateDietaryCategoriesTable = "create table if not exists DietaryCategories ( " +
                "ingredientID int ," +
                "dietaryCategory varchar(20) ," +
                "primary key ( ingredientID, dietaryCategory ) , " +
                "foreign key (ingredientID) references Ingredients(ingredientID) on delete cascade on update cascade )";


        try{
            Statement statement = connection.createStatement();

            //MenuItems Table
            statement.executeUpdate(queryCreateMenuItemsTable);
            numberOfTables++;

            //IngredientsTable Table
            statement.executeUpdate(queryCreateIngredientsTable);
            numberOfTables++;

            //IncludesTable Table
            statement.executeUpdate(queryCreateIncludesTable);
            numberOfTables++;

            //RatingsTable Table
            statement.executeUpdate(queryCreateRatingsTable);
            numberOfTables++;

            //DietaryCategories Table
            statement.executeUpdate(queryCreateDietaryCategoriesTable);
            numberOfTables++;

            //close
            statement.close();
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return numberOfTables;
    }

    @Override
    public int dropTables() {
        int numofDropped = 0;

        String queryDropMenuItemsTable = "drop table if exists MenuItems";

        String queryDropIngredientsTable = "drop table if exists Ingredients";

        String queryDropIncludesTable = "drop table if exists Includes";

        String queryDropRatingsTable = "drop table if exists Ratings";

        String queryDropDietaryCategories = "drop table if exists DietaryCategories";

        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(queryDropIncludesTable);
            numofDropped++;

            statement.executeUpdate(queryDropRatingsTable);
            numofDropped++;

            statement.executeUpdate(queryDropDietaryCategories);
            numofDropped++;

            statement.executeUpdate(queryDropMenuItemsTable);
            numofDropped++;

            statement.executeUpdate(queryDropIngredientsTable);
            numofDropped++;



            //close
            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }


        return numofDropped;
    }

    @Override
    public int insertMenuItems(MenuItem[] items) {

        int numOfRows=0;

        for(int i=0;i<items.length;i++)
        {
            try{
                MenuItem menIt = items[i];

                PreparedStatement stat= connection.prepareStatement("insert into MenuItems values(?,?,?,?)");

                stat.setInt(1,menIt.getItemID());
                stat.setString(2,menIt.getItemName());
                stat.setString(3,menIt.getCuisine());
                stat.setInt(4,menIt.getPrice());

                stat.executeUpdate();

                stat.close();
                numOfRows++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return numOfRows;
    }

    @Override
    public int insertIngredients(Ingredient[] ingredients) {

        int numOfRows=0;

        for(int i=0;i<ingredients.length;i++)
        {
            try{
                Ingredient inIt = ingredients[i];

                PreparedStatement stat= connection.prepareStatement("insert into Ingredients values(?,?)");

                stat.setInt(1,inIt.getIngredientID());
                stat.setString(2,inIt.getIngredientName());



                stat.executeUpdate();

                stat.close();
                numOfRows++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return numOfRows;
    }

    @Override
    public int insertIncludes(Includes[] includes) {
        int numOfRows=0;

        for(int i=0;i<includes.length;i++)
        {
            try{
                Includes inc = includes[i];

                PreparedStatement stat= connection.prepareStatement("insert into Includes values(?,?)");

                stat.setInt(1,inc.getItemID());
                stat.setInt(2,inc.getIngredientID());

                stat.executeUpdate();

                stat.close();
                numOfRows++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return numOfRows;
    }

    @Override
    public int insertDietaryCategories(DietaryCategory[] categories) {
        int numOfRows=0;

        for(int i=0;i<categories.length;i++)
        {
            try{
                DietaryCategory cat = categories[i];

                PreparedStatement stat= connection.prepareStatement("insert into DietaryCategories values(?,?)");

                stat.setInt(1,cat.getIngredientID());
                stat.setString(2,cat.getDietaryCategory());

                stat.executeUpdate();

                stat.close();
                numOfRows++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return numOfRows;
    }

    @Override
    public int insertRatings(Rating[] ratings) {
        int numOfRows=0;

        for(int i=0;i<ratings.length;i++)
        {
            try{
                Rating rat = ratings[i];

                PreparedStatement stat= connection.prepareStatement("insert into Ratings values(?,?,?,?)");

                stat.setInt(1,rat.getRatingID());
                stat.setInt(2,rat.getItemID());
                stat.setInt(3,rat.getRating());
                stat.setString(4,rat.getRatingDate());

                stat.executeUpdate();

                stat.close();
                numOfRows++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return numOfRows;
    }

    @Override
    public MenuItem[] getMenuItemsWithGivenIngredient(String name) {
        //3.3 Listing all menu items that include a given ingredient

        ResultSet res;
        ArrayList<MenuItem> resList = new ArrayList<>();

        try {
            //Listing all menu items that include a given ingredient
            PreparedStatement stat= connection.prepareStatement(
                    "SELECT DISTINCT M.itemID, M.itemName, M.cuisine, M.price\n" +
                    "FROM MenuItems M,Includes C, Ingredients G\n" +
                    "WHERE  G.ingredientName = ? and G.ingredientID = C.ingredientID and C.itemID=M.itemID\n" +
                    "ORDER BY M.itemID ASC;");

            stat.setString(1,name);
            res=stat.executeQuery();

            //after executing query putting results into our resul menuItem List
            while(res.next()){
                Integer itemID = res.getInt("itemID");
                String itemName = res.getString("itemName");
                String cuisine = res.getString("cuisine");
                Integer price = res.getInt("price");

                MenuItem men = new MenuItem(itemID,itemName,cuisine,price);
                resList.add(men);
            }

            //Close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        MenuItem[] resarray = new MenuItem[resList.size()];



        return resList.toArray(resarray);
    }

    @Override
    public MenuItem[] getMenuItemsWithoutAnyIngredient() {
        //3.4
        //Listing menu items that do not have any ingredients
        ResultSet res_set;
        ArrayList<MenuItem> resList = new ArrayList<>();

        try {
            String sql="SELECT DISTINCT M.itemID, M.itemName, M.cuisine, M.price\n"+
                       "FROM MenuItems M\n" +
                        "WHERE M.itemID NOT IN ( SELECT C.itemID " +
                                                "FROM Includes C) " +
                        "ORDER BY M.itemID ASC";

            PreparedStatement stat= connection.prepareStatement(sql);


            res_set=stat.executeQuery();

            //after executing query putting results into our resul menuItem List
            while(res_set.next()){
                Integer itemID = res_set.getInt("itemID");
                String itemName = res_set.getString("itemName");
                String cuisine = res_set.getString("cuisine");
                Integer price = res_set.getInt("price");

                MenuItem menu_item = new MenuItem(itemID,itemName,cuisine,price);
                resList.add(menu_item);
            }

            //Close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        MenuItem[] resarray = new MenuItem[resList.size()];


        return resList.toArray(resarray);
    }

    @Override
    public Ingredient[] getNotIncludedIngredients() {
        //3.5
        // Finding ingredients that have not been included in any menu items
        //Output: ingredientID, ingredientName


        ResultSet res_set;
        ArrayList<Ingredient> resList = new ArrayList<>();

        try {
            String sql="SELECT DISTINCT I.ingredientID, I.ingredientName "+
                    "FROM Ingredients I \n" +
                    "WHERE I.ingredientID NOT IN ( SELECT C.ingredientID " +
                    "FROM Includes C) " +
                    "ORDER BY I.ingredientID ASC";



            PreparedStatement stat= connection.prepareStatement(sql);


            res_set=stat.executeQuery();


            while(res_set.next()){
                Integer ingredientID = res_set.getInt("ingredientID");
                String ingredientName = res_set.getString("ingredientName");

                Ingredient ing = new Ingredient(ingredientID,ingredientName);
                resList.add(ing);
            }

            //Close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        Ingredient[] resarray = new Ingredient[resList.size()];


        return resList.toArray(resarray);
    }

    @Override
    public MenuItem getMenuItemWithMostIngredients() {
        //3.6
        //Finding the menu item that includes the highest
        //number of different ingredients
        //Output: itemID, itemName, cuisine, price

        ResultSet res_set;
        ArrayList<MenuItem> resList = new ArrayList<>();

        try {
            String sql="SELECT DISTINCT M.itemID, M.itemName,M.cuisine,M.price\n"+
                    "FROM MenuItems M\n" +
                    "WHERE M.itemID = ( select Temp.itemID\n" +
                    "FROM (SELECT  C.itemID,COUNT(*) as scount\n" +
                    "\t\tFROM Includes C\n" +
                    "\t\tGROUP BY C.itemID) as Temp\n" +
                    "WHERE Temp.scount = (SELECT MAX(Temp1.scount) FROM (SELECT  COUNT(*) as scount\n" +
                    "\t\tFROM Includes C\n" +
                    "\t\tGROUP BY C.itemID ) as Temp1 ) )" +
                    "ORDER BY M.itemID ASC ";

            PreparedStatement stat= connection.prepareStatement(sql);


            res_set=stat.executeQuery();

            while(res_set.next()){
                Integer itemID = res_set.getInt("itemID");
                String itemName = res_set.getString("itemName");
                String cuisine = res_set.getString("cuisine");
                Integer price = res_set.getInt("price");

                MenuItem menu_item = new MenuItem(itemID,itemName,cuisine,price);
                resList.add(menu_item);
            }

            //Close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        MenuItem[] resarray = new MenuItem[resList.size()];


        return resList.toArray(resarray)[0];

    }

    @Override
    public QueryResult.MenuItemAverageRatingResult[] getMenuItemsWithAvgRatings() {
        //3.7
        //Listing the average rating of each menu item
        //Output: itemID, itemName, avgRating
        //Order the results by descending avgRating

        ResultSet res_set;
        ArrayList<QueryResult.MenuItemAverageRatingResult> resList = new ArrayList<>();

        try {
            String sql="Select M.itemID,M.itemName,AVG(R.rating) as avgRating " +
                    "From MenuItems M Left Join Ratings R  ON R.itemID=M.itemID " +
                    "Group BY M.itemID " +
                    "Order By avgRating DESC;";
            Statement stat= connection.prepareStatement(sql);


            res_set=stat.executeQuery(sql);

            //after executing query putting results into our resul menuItem List
            while(res_set.next()){
                String itemID = res_set.getString("itemID");
                String itemName = res_set.getString("itemName");
                String avgRating = res_set.getString("avgRating");

                QueryResult.MenuItemAverageRatingResult menu_item = new QueryResult.MenuItemAverageRatingResult(itemID,itemName,avgRating);
                resList.add(menu_item);
            }

            //Close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.MenuItemAverageRatingResult[] resarray = new QueryResult.MenuItemAverageRatingResult[resList.size()];



        return resList.toArray(resarray);
    }

    @Override
    public MenuItem[] getMenuItemsForDietaryCategory(String category) {
        //3.8 Listing menu items suitable to a given dietary category
        //For a menu item to be suitable to a given dietary category givenCategory, all the ingredients of this
        //menu item should be from the given dietary category.
        //Method(Input): getMenuItemsForDietaryCategory(givenCategory)
        //Output: itemID, itemName, cuisine, price
        //Order the results by ascending itemID

        ResultSet res_set;
        ArrayList<MenuItem> resList = new ArrayList<>();

        try {
            String sql="SELECT M.itemID,M.itemName,M.cuisine,M.price FROM MenuItems M WHERE NOT EXISTS  " +
                    "( Select C.ingredientID FROM Includes C WHERE C.itemID = M.itemID AND NOT EXISTS " +
                    " (Select D.ingredientID FROM DietaryCategories D WHERE D.dietaryCategory = ? AND D.ingredientID = C.ingredientID)) " +
                    "AND EXISTS (SELECT * FROM Includes C2 WHERE M.itemID = C2.itemID )";

            PreparedStatement stat= connection.prepareStatement(sql);
            stat.setString(1,category);

            res_set=stat.executeQuery();

            //after executing query putting results into our resul menuItem List
            while(res_set.next()){
                Integer itemID = res_set.getInt("itemID");
                String itemName = res_set.getString("itemName");
                String cuisine = res_set.getString("cuisine");
                Integer price = res_set.getInt("price");

                MenuItem menu_item = new MenuItem(itemID,itemName,cuisine,price);
                resList.add(menu_item);
            }

            //Close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        MenuItem[] resarray = new MenuItem[resList.size()];


        return resList.toArray(resarray);
    }

    @Override
    public Ingredient getMostUsedIngredient() {
        //3.9 Finding the most used ingredient across all menu items
        //Method: getMostUsedIngredient()
        //Output: ingredientID, ingredientName

        ResultSet res_set;
        ArrayList<Ingredient> resList = new ArrayList<>();

        try {
            String sql="Select C.ingredientID, I.ingredientName, count(*) as scount \n" +
                    "From Includes C, Ingredients I\n" +
                    "Where C.ingredientID = I.ingredientID\n" +
                    "Group by C.ingredientID\n" +
                    "Having Count(*) >=ALL ( Select count(*) from Includes C1 Group by C1.ingredientID );\n";



            PreparedStatement stat= connection.prepareStatement(sql);



            res_set=stat.executeQuery();


            while(res_set.next()){
                Integer ingredientID = res_set.getInt("ingredientID");
                String ingredientName = res_set.getString("ingredientName");

                Ingredient ing = new Ingredient(ingredientID,ingredientName);
                resList.add(ing);
            }

            //Close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        Ingredient[] resarray = new Ingredient[resList.size()];


        return resList.toArray(resarray)[0];


    }

    @Override
    public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgRating() {
        //3.10 Finding the cuisines with the average rating of
        //menu items belonging to that cuisine
        //For each cuisine, you need to find the average rating of menu items belonging to that cuisine.
        //note: Having no rating DOES NOT MEAN having a 0-rating. You should not include the 0-ratings in
        //the average, and for the cuisines with no ratings, you should return NULL.
        //Method: getCuisinesWithAvgRating()
        //Output: cuisine, averageRating
        //Order the results by descending averageRating

        ResultSet res_set;
        ArrayList<QueryResult.CuisineWithAverageResult> resList = new ArrayList<>();

        try {
            String sql="Select Temp.cuisine, avg(Temp.rating) as average \n" +
                    "From (SELECT M.itemID, M.cuisine, R.rating\n" +
                    "        FROM MenuItems M Left join Ratings R on  M.itemID = R.itemID\n" +
                    "        ) as Temp\n" +
                    "group by Temp.cuisine\n" +
                    "order by avg(Temp.rating) DESC;";

            Statement stat= connection.prepareStatement(sql);


            res_set=stat.executeQuery(sql);

            //after executing query putting results into our resul menuItem List
            while(res_set.next()){
                String cuisineName = res_set.getString("cuisine");
                String average = res_set.getString("average");


                QueryResult.CuisineWithAverageResult cuisine = new QueryResult.CuisineWithAverageResult(cuisineName,average);
                resList.add(cuisine);
            }

            //Close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();

        }


        QueryResult.CuisineWithAverageResult[] resarray = new QueryResult.CuisineWithAverageResult[resList.size()];

        return resList.toArray(resarray);
    }

    @Override
    public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgIngredientCount() {
        //3.11 Finding the average ingredient count of menu items
        //in each cuisine
        //For each cuisine, you need to find the average ingredient count of menu items belonging to that cuisine.
        //note: Having no ingredient MEANS having 0 ingredients. You should include them in the average.
        //Method: getCuisinesWithAvgIngredientCount()
        //Output: cuisine, averageCount
        //Order the results by descending averageCount
        ResultSet res_set;
        ArrayList<QueryResult.CuisineWithAverageResult> resList = new ArrayList<>();

        try {
            String sql="Select Temp.cuisine, avg(Temp.scount) as average\n" +
                    "from (select  M.cuisine,M.itemID, count(C.`ingredientID`) as scount\n" +
                    "from `MenuItems` M Left join `Includes` C on  M.`itemID` = C.itemID\n" +
                    "group by M.cuisine,M.`itemID`) as Temp\n" +
                    "group by Temp.cuisine\n " +
                    "Order by average DESC;";

            Statement stat= connection.prepareStatement(sql);


            res_set=stat.executeQuery(sql);

            //after executing query putting results into our resul menuItem List
            while(res_set.next()){
                String cuisineName = res_set.getString("cuisine");
                String average = res_set.getString("average");


                QueryResult.CuisineWithAverageResult cuisine = new QueryResult.CuisineWithAverageResult(cuisineName,average);
                resList.add(cuisine);
            }

            //Close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();

        }


        QueryResult.CuisineWithAverageResult[] resarray = new QueryResult.CuisineWithAverageResult[resList.size()];

        return resList.toArray(resarray);

    }

    @Override
    public int increasePrice(String ingredientName, String increaseAmount) {
        //3.12 Increasing the price of all menu items that include
        //a given ingredient by a given amount
        //If the given ingredient is included in a menu item, you need to increase the price of that menu item by
        //the given amount.
        //Method(Inputs): increasePrice(givenIngredient, givenAmount)
        //Output: number of rows affected

        int numberofRowsAffected = 0;

        try {

            PreparedStatement stat=connection.prepareStatement("\n" +
                    "Update `MenuItems` M\n" +
                    "SET M.price = M.price + ?       \n" +
                    "Where M.itemID IN ( Select C.itemID\n" +
                    "        From `Includes` C, `Ingredients` G\n" +
                    "        Where G.`ingredientName` = ? AND G.ingredientID = C.ingredientID ) ;");

            stat.setString(1,increaseAmount);
            stat.setString(2,ingredientName);
            numberofRowsAffected=stat.executeUpdate();

            //close
            stat.close();

        } catch (SQLException e) {
            e.printStackTrace();

        }


        return numberofRowsAffected;

    }

    @Override
    public Rating[] deleteOlderRatings(String date) {
        //3.13 Deleting all ratings that have an earlier rating date
        //than a given date
        //Method(Input): deleteOlderRatings(givenDate)
        //Output: ratingID, itemID, rating, ratingDate
        //Order the deleted rows by ascending ratingID


        ResultSet res_set;
        ArrayList<Rating> resList = new ArrayList<>();

        try {
            PreparedStatement stat = connection.prepareStatement("Select Distinct R.ratingID,R.itemID,R.rating,R.ratingDate " +
                                                                    " From Ratings R WHERE R.ratingDate < ? ;");
            stat.setString(1,date);
            res_set = stat.executeQuery();
            while(res_set.next()){
                Integer ratingID = res_set.getInt("ratingID");
                Integer itemID = res_set.getInt("itemID");
                Integer rating = res_set.getInt("rating");
                String ratingDate = res_set.getString("ratingDate");

                Rating rat = new Rating(ratingID,itemID,rating,ratingDate);
                resList.add(rat);
            }

            try {
                PreparedStatement stat2 = connection.prepareStatement(" Delete From Ratings Where ratingDate < ? ;");
                stat2.setString(1,date);

                stat2.executeUpdate();

                stat2.close();

            }
            catch (SQLException e){
                e.printStackTrace();
            }

            stat.close();
        }
        catch (SQLException e){
            e.printStackTrace();
        }


        Rating[] resArray = new Rating[resList.size()];
        return resList.toArray(resArray);
    }
}
