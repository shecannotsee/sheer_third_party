//
// Created by shecannotsee on 2022/11/7.
//

#ifndef SQLITE3_TEST_SQLITE_ORM_TEST_HEADER_H_
#define SQLITE3_TEST_SQLITE_ORM_TEST_HEADER_H_

#include <iostream>
#include <sqlite_orm/sqlite_orm.h>
#include <unistd.h>

/* create table */
namespace method1 {
struct User{
  int id;
  std::string firstName;
  std::string lastName;
  int birthDate;
  std::unique_ptr<std::string> imageUrl;
  int typeId;
};

struct UserType {
  int id;
  std::string name;
};

using namespace sqlite_orm;
void main() {
  // 建立映射前需要通过sqlite创建对应的数据库以及表
  auto storage =
      make_storage("../test.db",
                   make_table("users",
                              make_column("id", &User::id, primary_key().autoincrement(),primary_key()),
                              make_column("first_name",&User::firstName),
                              make_column("last_name",&User::lastName),
                              make_column("birth_date",&User::birthDate),
                              make_column("image_url",&User::imageUrl),
                              make_column("type_id",&User::typeId)),
                   make_table("user_types",
                              make_column("id",&UserType::id), primary_key().autoincrement(),primary_key(),
                              make_column("name", &UserType::name, default_value("name_placeholder")))
                   );

  /* clear */ {
    for (auto& user : storage.iterate<User>()) {
      storage.remove<User>(user.id);
    }
  };
  /* insert */ {
    std::cout<<"\ninsert test:\n";
    User firstUser{-1, "Jonh", "Doe", 664416000, std::make_unique<std::string>("url_to_heaven"), 3};
    auto insertedId = storage.insert(firstUser);
    std::cout << "first user  insertedId = " << insertedId << std::endl;
    firstUser.id = insertedId;

    User secondUser{-1, "Alice", "Inwonder", 831168000, {}, 2};
    insertedId = storage.insert(secondUser);
    std::cout << "second user insertedId = " << insertedId << std::endl;
    secondUser.id = insertedId;

    // insert from id=99,autoincrement
    // 用此方法可以强行从中间插入新的数据，否则自动获取主键id会记录到已经删除的id然后在后面增加
    User use_id_insert_User{99, "xxxx", "123", 664416000, std::make_unique<std::string>("url_to_heaven"), 3};
    try {
      storage.replace(use_id_insert_User);
      std::cout<<"insert success."<<std::endl;
    } catch (std::system_error& ec){
      std::cout<<"insert error :"<<ec.what()<<std::endl;
    };
  };
  /* update */ {
    // 逐行更新方法,更新第一行数据
    User userUpdate;
    userUpdate.firstName = "update_firstNamex";
    userUpdate.lastName = "update_lastName";
    storage.update(userUpdate);
    // 全体更新,但是实际上这种写法是通过where更新
    storage.update_all(set(c(&User::lastName) = "Hardey",
                           c(&User::typeId) = 2),
                       where(c(&User::firstName) == "Jonh"));
  };
  /* delete */ {
    std::cout<<"\ndelete test:\n";
    // 通过id删除数据
    int deleteId = 0;
    try {
      storage.remove<User>(deleteId);
      std::cout<<"delete success.\n";
    } catch (std::system_error& ec) {
      std::cout<<"delete error :"<<ec.what()<<std::endl;
    }
  };
  /* select */ {
    std::cout<<"\nselect test:\n";
    // select where id=99
    std::cout<<"select by id.\n";
    int insertedId = 98;
    if (auto user = storage.get_pointer<User>(insertedId)) {
      std::cout << "user = " << user->firstName << " " << user->lastName << std::endl;
    } else {
      std::cout << "no user with id " << insertedId << std::endl;
    }
    // select all
    std::vector<User> allUsers = storage.get_all<User>();
    std::cout << "allUsers (" << allUsers.size() << "):" << std::endl;
    for(auto &user : allUsers) {
      std::cout << storage.dump(user) << std::endl; //  dump returns std::string with json-like style object info. For example: { id : '1', first_name : 'Jonh', last_name : 'Doe', birth_date : '664416000', image_url : 'https://cdn1.iconfinder.com/data/icons/man-icon-set/100/man_icon-21-512.png', type_id : '3' }
    }
    // select all one by one
    std::cout<<"select all one by one.\n";
    for (auto& user : storage.iterate<User>()) {
      std::cout<< storage.dump(user) <<std::endl;
    }
  };
  /* where conditions */ {
    // SELECT * FROM users WHERE id < 10
    std::cout<<"SELECT * FROM users WHERE id < 10;\n";
    auto idLesserThan10 = storage.get_all<User>(where(c(&User::id) < 10));
    std::cout << "idLesserThan10 count = " << idLesserThan10.size() << std::endl;
    for(auto &user : idLesserThan10) {
      std::cout << storage.dump(user) << std::endl;
    }
    // SELECT * FROM users WHERE first_name != 'John'
    std::cout<<"SELECT * FROM users WHERE first_name != 'John';\n";
    auto notJohn = storage.get_all<User>(where(c(&User::firstName) != "John"));
    std::cout << "notJohn count = " << notJohn.size() << std::endl;
    for(auto &user : notJohn) {
      std::cout << storage.dump(user) << std::endl;
    }
    // more where
    std::cout<<"!not and or (where id >= 5 and id <= 7 and not id = 6)\n";
    auto id5and7 = storage.get_all<User>(where(c(&User::id) <= 7 and c(&User::id) >= 5 and not (c(&User::id) == 6)));
    std::cout << "id5and7 count = " << id5and7.size() << std::endl;
    for(auto &user : id5and7) {
      std::cout << storage.dump(user) << std::endl;
    }
    // SELECT * FROM users WHERE id IN (2, 4, 6, 8, 10)
    std::cout<<"SELECT * FROM users WHERE id IN (2, 4, 6, 8, 10);\n";
    auto evenLesserTen10 = storage.get_all<User>(where(in(&User::id, {2, 4, 6, 8, 10})));
    std::cout << "evenLesserTen10 count = " << evenLesserTen10.size() << std::endl;
    for(auto &user : evenLesserTen10) {
      std::cout << storage.dump(user) << std::endl;
    }

    // SELECT * FROM users WHERE last_name IN ("Doe", "White")
    std::cout<<"SELECT * FROM users WHERE last_name IN (\"Doe\", \"White\")\n";
    auto doesAndWhites = storage.get_all<User>(where(in(&User::lastName, {"Doe", "White"})));
    std::cout << "doesAndWhites count = " << doesAndWhites.size() << std::endl;
    for(auto &user : doesAndWhites) {
      std::cout << storage.dump(user) << std::endl;
    }
    // SELECT * FROM users WHERE id BETWEEN 66 AND 68
    std::cout<<"SELECT * FROM users WHERE id BETWEEN 66 AND 68;";
    auto betweenId = storage.get_all<User>(where(between(&User::id, 66, 68)));
    std::cout << "betweenId = " << betweenId.size() << std::endl;
    for(auto &user : betweenId) {
      std::cout << storage.dump(user) << std::endl;
    }
    // SELECT * FROM users WHERE last_name LIKE 'D%'
    std::cout<<"SELECT * FROM users WHERE last_name LIKE 'D%'\n";
    auto whereNameLike = storage.get_all<User>(where(like(&User::lastName, "D%")));
    std::cout << "whereNameLike = " << whereNameLike.size() << std::endl;
    for(auto &user : whereNameLike) {
      std::cout << storage.dump(user) << std::endl;
    }
    // SELECT * FROM users ORDER BY id
    std::cout<<"SELECT * FROM users ORDER BY id\n";
    auto orderedUsers = storage.get_all<User>(order_by(&User::id));
    std::cout << "orderedUsers count = " << orderedUsers.size() << std::endl;
    for(auto &user : orderedUsers) {
      std::cout << storage.dump(user) << std::endl;
    }
    // SELECT * FROM users WHERE id > 250 ORDER BY id LIMIT 5
    std::cout<<"SELECT * FROM users WHERE id > 250 ORDER BY id LIMIT 5\n";
    auto limited5 = storage.get_all<User>(where(c(&User::id) > 250),
                                          order_by(&User::id),
                                          limit(5));
    std::cout << "limited5 count = " << limited5.size() << std::endl;
    for(auto &user : limited5) {
      std::cout << storage.dump(user) << std::endl;
    }

    // SELECT * FROM users WHERE id > 250 ORDER BY id LIMIT 5, 10
    std::cout<<"SELECT * FROM users WHERE id > 250 ORDER BY id LIMIT 5, 10\n";
    auto limited5comma10 = storage.get_all<User>(where(c(&User::id) > 250),
                                                 order_by(&User::id),
                                                 limit(5, 10));
    std::cout << "limited5comma10 count = " << limited5comma10.size() << std::endl;
    for(auto &user : limited5comma10) {
      std::cout << storage.dump(user) << std::endl;
    }

    // SELECT * FROM users WHERE id > 250 ORDER BY id LIMIT 5 OFFSET 10
    std::cout<<"SELECT * FROM users WHERE id > 250 ORDER BY id LIMIT 5 OFFSET 10";
    auto limit5offset10 = storage.get_all<User>(where(c(&User::id) > 250),
                                                order_by(&User::id),
                                                limit(5, offset(10)));
    std::cout << "limit5offset10 count = " << limit5offset10.size() << std::endl;
    for(auto &user : limit5offset10) {
      std::cout << storage.dump(user) << std::endl;
    }
  };

};

};// namespace method1

#endif //SQLITE3_TEST_SQLITE_ORM_TEST_HEADER_H_
