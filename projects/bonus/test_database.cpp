#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "Database.hpp"


struct Entry {
    std::string title;
    std::string author;
    int pubYear;
    bool operator==(const Entry&) const; 
};

bool Entry::operator==(const Entry& e) const {
    return (title == e.title) && (author == e.author) && (pubYear == e.pubYear);
}


TEST_CASE("Test Construction", "[construction]") {
    Database<std::string> testdb;

    REQUIRE(testdb.isEmpty());
}


TEST_CASE("Test Add", "[add]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);
    REQUIRE(!testdb.isEmpty());
    REQUIRE(testdb.contains("key1"));
    REQUIRE(testdb.contains("key2"));
}


TEST_CASE("Test Duplicate Add", "[duplicate add]") {
    Database<std::string> testdb;
    std::string e1 = "entry";
    
    testdb.add("key1", "key2", e1);
    REQUIRE(!testdb.add("key1", "key2", e1));
}


TEST_CASE("Test Retrieve", "[retrieve]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);
    
    REQUIRE(testdb.getValue("key1") == e1);
    REQUIRE(testdb.getValue("key2") == e1);
}


TEST_CASE("Test Add 2", "[add 2]") {
    Database<std::string> testdb;
    std::string e1 = "entry1";
    std::string e2 = "entry2";
    
    testdb.add("key1a", "key1b", e1);
    testdb.add("key2a", "key2b", e2);

    REQUIRE(testdb.getNumberOfEntries() == 2);

    REQUIRE(testdb.getValue("key1a") == e1);
    REQUIRE(testdb.getValue("key1b") == e1);
    REQUIRE(testdb.getValue("key2a") == e2);
    REQUIRE(testdb.getValue("key2b") == e2);
}


TEST_CASE("Test Remove", "[remove]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);
    
    testdb.remove("key1");
    REQUIRE(!testdb.contains("key1"));
    REQUIRE(!testdb.contains("key2"));

    testdb.add("key1", "key2", e1);
    
    testdb.remove("key2");
    REQUIRE(!testdb.contains("key1"));
    REQUIRE(!testdb.contains("key2"));

    REQUIRE(testdb.isEmpty());
}


TEST_CASE("Test Copy Construct", "[copy]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);

    Database<std::string> testdb_copy(testdb);

    REQUIRE(testdb_copy.getValue("key1") == e1);
    REQUIRE(testdb_copy.getValue("key2") == e1); 
}


TEST_CASE("Test Copy Assign", "[copy assign]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);

    Database<std::string> testdb_copy;

    testdb_copy = testdb;

    REQUIRE(testdb_copy.getValue("key1") == e1);
    REQUIRE(testdb_copy.getValue("key2") == e1); 
}


TEST_CASE("Test Entry Types", "[entry type]") {
    Database<Entry> testdb;

    Entry e1;
    std::string isbn1 = "000-0-00-000000-1";
    std::string catalog_id1 = "0000001";
    e1.title = "The Winds of Winter";
    e1.author = "George R. R. Martin";
    e1.pubYear = 2031;

    testdb.add(isbn1, catalog_id1, e1);

    Entry e2;

    std::string isbn2 = "000-0-00-000000-2";
    std::string catalog_id2 = "0000002";
    e2.title = "A Dream of Spring";
    e2.author = "George R. R. Martin";
    e2.pubYear = 2032;

    testdb.add(isbn2, catalog_id2, e2);
}
//****************************added tests*********************


struct Entry2 {
    std::string employeeName;
    std::string employeeTitle;
    int numHoursWorked;
    bool operator==(const Entry2&) const; 
};
bool Entry2::operator==(const Entry2& e) const {
    return (employeeName == e.employeeName) && (employeeTitle == e.employeeTitle) && (numHoursWorked == e.numHoursWorked);
};

TEST_CASE("Test default construction","[default construction Entry2]"){
    Database<Entry2> testdb;
    REQUIRE(testdb.getNumberOfEntries()==0);
    REQUIRE(testdb.isEmpty());


}

TEST_CASE("Adding to employee information while checking for duplicates", "[add Entry2]") {
    Database<Entry2> employeeInfo;

    Entry2 carol;
    Entry2 bob;
    Entry2 jim;

    carol.employeeName = "Carol";
    carol.employeeTitle = "Manager";
    carol.numHoursWorked = 40;

    bob.employeeName = "Bob";
    bob.employeeTitle = "Cashier";
    bob.numHoursWorked = 37;

    jim.employeeName = "Jim";
    jim.employeeTitle = "Delivery Driver";
    jim.numHoursWorked = 10;

    REQUIRE(employeeInfo.add("Carol", "Manager", carol));
    REQUIRE(employeeInfo.add("Bob", "Cashier", bob));
    REQUIRE(employeeInfo.add("Jim", "Delivery Driver", jim));

    REQUIRE(!employeeInfo.add("Carol", "Manager", carol)); // check for dups
    REQUIRE(!employeeInfo.add("Bob", "Cashier", bob));    
    REQUIRE(!employeeInfo.add("Jim", "Delivery Driver", jim)); 

    REQUIRE(employeeInfo.getNumberOfEntries() == 3);
}

TEST_CASE("Employee information: getting employee information", "[retrieve Entry2]") {
    Database<Entry2> employeeInfo;

    Entry2 carol;
    Entry2 bob;
    Entry2 jim;

    carol.employeeName = "Carol";
    carol.employeeTitle = "Manager";
    carol.numHoursWorked = 40;

    bob.employeeName = "Bob";
    bob.employeeTitle = "Cashier";
    bob.numHoursWorked = 37;

    jim.employeeName = "Jim";
    jim.employeeTitle = "Delivery Driver";
    jim.numHoursWorked = 10;

    employeeInfo.add("Carol", "Manager", carol);
    employeeInfo.add("Bob", "Cashier", bob);
    employeeInfo.add("Jim", "Delivery Driver", jim);

    REQUIRE(employeeInfo.getValue("Carol") == carol);
    REQUIRE(employeeInfo.getValue("Bob") == bob);
    REQUIRE(employeeInfo.getValue("Jim") == jim);
}

TEST_CASE("Removing employee information", "[remove Entry2]") {
    Database<Entry2> employeeInfo;

    Entry2 carol;
    Entry2 bob;
    Entry2 jim;

    carol.employeeName = "Carol";
    carol.employeeTitle = "Manager";
    carol.numHoursWorked = 40;

    bob.employeeName = "Bob";
    bob.employeeTitle = "Cashier";
    bob.numHoursWorked = 37;

    jim.employeeName = "Jim";
    jim.employeeTitle = "Delivery Driver";
    jim.numHoursWorked = 10;

    employeeInfo.add("Carol", "Manager", carol);
    employeeInfo.add("Bob", "Cashier", bob);
    employeeInfo.add("Jim", "Delivery Driver", jim);

    REQUIRE(employeeInfo.remove("Bob"));
    REQUIRE(!employeeInfo.contains("Bob"));

    REQUIRE(employeeInfo.remove("Jim"));
    REQUIRE(!employeeInfo.contains("Jim"));

    REQUIRE(employeeInfo.remove("Carol"));
    REQUIRE(!employeeInfo.contains("Carol"));
    REQUIRE(employeeInfo.isEmpty());
}