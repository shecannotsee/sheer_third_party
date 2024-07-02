//
// Created by shecannotsee on 2022/11/3.
//

#ifndef URL_MAP_TEST_JWT_CPP_TEST_HEADER_H_
#define URL_MAP_TEST_JWT_CPP_TEST_HEADER_H_
#include <iostream>
#include <string>
#include <unistd.h>
#include <jwt-cpp/jwt.h>

namespace method1 {

void main() noexcept {
  /* 解析token,不依赖openssl,仅需要jwt-cpp库即可 */ {
    std::cout<<"\n解析token test:\n";
    std::string token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJpc3MiOiJhdXRoMCJ9.AbIJTDMFc7yUa5MhvcP03nJPyCPzZtQcGEp-zWfOkEE";
    auto decoded = jwt::decode(token);
    for(auto& e : decoded.get_payload_json())
      std::cout << e.first << " = " << e.second << std::endl;
  };

  /* 生成token,依赖需要添加openssl,因为涉及到一些加密解密算法 */ {
    std::cout<<"\n生成token test:\n";
    auto token = jwt::create()
    /*1*/.set_issuer("auth0") // default,token签发人
    /*2*/.set_type("JWS") // default
    /*3*/.set_issued_at(std::chrono::system_clock::now()) // 设置有效时间
         .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{10}) // 按秒来处理,3600s = 1hour
    /*4*/.set_payload_claim("key1", jwt::claim(std::string("value1")))  //jwt PAYLOAD:DATA other k-v
        .sign(jwt::algorithm::hs256{"secret"}); // default
    std::cout<<token<<std::endl;
    // print:
    //    eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9
    //    .eyJleHAiOjE2Njc0NDM0ODksImlhdCI6MTY2NzQ0MzQ3OSwiaXNzIjoiYXV0aDAiLCJrZXkxIjoidmFsdWUxIn0
    //    .nLD8Fx9HmnPbT_B2II-9J3GQjvwV-WhoFDDQIspaFoU
    auto decoded = jwt::decode(token);
    for(auto& e : decoded.get_payload_json()) {
      std::cout << e.first << " = " << e.second << std::endl;
      // print:
      //    exp = 1667443348  /*3*/
      //    iat = 1667443338  /*3*/
      //    iss = "auth0"     /*1*/
      //    key1 = "value1"   /*4*/
    }
  };

  /* token认证 */ {
    std::cout<<"\ntoken 认证:\n";
    // 1.生成验证令牌
    jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson> verifier{jwt::default_clock{}};
    verifier =
//    auto verifier =
        jwt::verify()
        .allow_algorithm(jwt::algorithm::hs256{"secret"}) // 验证算法
        .with_claim("user",jwt::claim(std::string("carry"))) // 验证token中需要有k-v : "user":"carry"
        .with_issuer("auth01"); // 验证颁发者
    std::cout<<"令牌条件为:1.默认算法;  2.颁发者为auth01;  3.字段需要有user:carry\n";

    auto token = jwt::create()
      /*1*/.set_issuer("auth01") // default,token签发人
      /*2*/.set_type("JWS") // default
      /*3*/.set_issued_at(std::chrono::system_clock::now()) // 设置有效时间
           .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{10}) // 按秒来处理,3600s = 1hour
      /*4*/.set_payload_claim("user", jwt::claim(std::string("carry")))  //jwt PAYLOAD:DATA other k-v
           .sign(jwt::algorithm::hs256{"secret"}); // default
    std::cout<<"生成token信息为:1.默认算法  2.颁发者为auth01  3.字段有user:carry  4.时效为10s  5.类型为JWS\n";
    std::cout<<token<<std::endl;
v:
    // 该认证函数通过抛出异常来处理验证失败的问题
    try {
      verifier.verify(jwt::decode(token)); // 验证的输入应为特殊(用'.'分隔)base64URL解码后的内容,实际上是一个json
      std::cout<<"认证成功\n";
    } catch (std::system_error& ec) {
      std::cout<<"认证失败 : "<< ec.what()<<std::endl;
      // HACK:若要启用下面这行,则需要处理异常,若不启用,则不应该在catch范围之后编写任何代码,因为在catch范围之后的任何代码都会被执行
      // throw;
    };
    std::cout<<"no throw\n";
    sleep(5);//由于token时效设置的10s,所以在此处进行认证时,前两次认证会成功,后续的认证会失败,因为token已经过了时效
    goto v;
  };
};

};// namespace method1


namespace method2 {
void main() {
  auto token = jwt::create()
      .set_issuer("WPHS")
      .set_type("JWS")
      .set_payload_claim("name", jwt::claim(std::string("admin")))
      .sign(jwt::algorithm::hs256{"secret"});

  if (typeid(token)== typeid(std::string)) {
    std::cout<<"token is:" <<token<<std::endl;
  }

  jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson> verifier{jwt::default_clock{}};
  verifier = jwt::verify()
      .allow_algorithm(jwt::algorithm::hs256{"secret"})
      .with_claim("name", jwt::claim(std::string("admin")))
      .with_issuer("WPHS");

  try {
    verifier.verify(jwt::decode(token));
    std::cout<<"verify success.\n";
  } catch (std::exception ec) {
    std::cout<<ec.what()<<std::endl;
  }
}
};// namespace method2

#endif //URL_MAP_TEST_JWT_CPP_TEST_HEADER_H_
