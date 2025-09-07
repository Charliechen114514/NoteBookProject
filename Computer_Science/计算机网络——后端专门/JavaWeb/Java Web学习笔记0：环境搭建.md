# 在WSL下搭建JavaWeb: JDBC学习环境

## 前言

​	笔者最近打算放松一下，接触一点经典的Java Web技术，自己在闲暇时间时玩一玩JavaWeb技术。这里开一个小系列整理一下最近学习的东西，以供参考和学习。

​	笔者的计划是使用VSCode写代码，使用的是Java21，仓库管理因为之前小小的接触过Gradle感觉它实在是太重太重了，没啥兴趣。所以决定采用Maven来管理项目。这篇博客也是记录一下如何搞这个小事情。当然，笔者喜欢在WSL或者是Linux下写代码。因此，我使用的是Ubuntu24.04的WSL镜像。

​	由于是侧重于JDBC，我使用的是Mariadb这个开源的数据库。这里的教程的大致步骤是如下的：

- 安装 MariaDB（或远程服务器可访问）
- 安装 JDK21
- 使用Maven管理和添加我们的项目

## 最基础的环境安装

关于VSCode，WSL的安装，笔者认为互联网上已经满大街的教程，这里不浪费口舌了。

## Mariadb安装

#### Mariadb安装

安装Mariadb还是很简单的：

```bash
sudo apt update
sudo apt install mariadb-server
```

一般而言，我们最好执行安全配置脚本，这样的话我们的数据库才会安全一些

```bash
sudo mysql_secure_installation
```

按照提示设置 root 密码、删除匿名用户、禁止远程 root 登录、删除 test 数据库等。

#### 登录 MariaDB 并测试

```bash
sudo mariadb -u root -p
```

首次如果没有设置密码，可以不加 `-p` 登录，之后再设置：

```sql
ALTER USER 'root'@'localhost' IDENTIFIED BY 'your_new_password'; 
FLUSH PRIVILEGES;
```

your_new_password注意换成自己的密码奥！

#### 准备一个超级简单的数据库备用（可放到后面写JavaWeb代码的时候再说）

这里就发挥自己的SQL语句水平就好

```sql
CREATE DATABASE webapp_db DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER 'webuser'@'localhost' IDENTIFIED BY 'webpass';
GRANT ALL PRIVILEGES ON webapp_db.* TO 'webuser'@'localhost';
FLUSH PRIVILEGES;
```

​	这将创建一个名为 `webapp_db` 的数据库，并允许 `webuser` 用户以密码 `webpass` 访问它。

## 安装Java

​	我们使用的是Java，安装java-jdk就好了

```bash
sudo apt update
sudo apt install openjdk-21-jdk
```

​	为了检查自己的环境问题，你可以尝试一下检查版本

```bash
java --version
javac --version
```

​	安装过后，如果版本没问题，我们的结果会是这样的：

```bash
charliechen@Charliechen:~/javaee/jdbc$ java --version
openjdk 21.0.7 2025-04-15
OpenJDK Runtime Environment (build 21.0.7+6-Ubuntu-0ubuntu124.04)
OpenJDK 64-Bit Server VM (build 21.0.7+6-Ubuntu-0ubuntu124.04, mixed mode, sharing)
charliechen@Charliechen:~/javaee/jdbc$ javac --version
javac 21.0.7
```

## 使用Maven创建基本的工具

​	可能有朋友不太熟悉Maven，一句简单的话就是相当于项目管理器，Maven会托管你的项目的依赖和版本等等，保证一定的可移植性。

​	我们这里在VSCode下载Java和Maven的插件（Extension Pack for Java）之后，我们摁住Ctrl + Shift + P，选择Java：创建项目（有可能是英文，我相信看我博客朋友的英文水平，好吧，如果真不知道的话是Create Java Projects），选择使用Maven创建项目，模板笔者认为无伤大雅，随意选择后。我们的项目描述文件放在一个XML描述文件里了。这里我们首先需要把Java的版本修正对：

```xml
  <properties>
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    <maven.compiler.source>21</maven.compiler.source>
    <maven.compiler.target>21</maven.compiler.target>
  </properties>
```

​	在dependencies的节点下，追加

```xml
    <dependency>
      <groupId>org.mariadb.jdbc</groupId>
      <artifactId>mariadb-java-client</artifactId>
      <version>3.3.1</version>
    </dependency>
```

​	这个就是Mariadb的JDBC驱动器，我们使用这个小玩意来作为JDBC接口的实际实现。然后我们可以开始写代码测试一下：

```java
package com.example;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        String databases_name = "my_first_db";
        // 这个是字符串的格式，我偷懒了没用format，不太规范
        // jdbc:mariadb:是协议命，这是JDBC驱动的规范，以及，如果你是使用其他的数据库，
        // mariadb就需要换成别的，比如说mysql数据库换成mysql
        String url = "jdbc:mariadb://localhost:3306/" + databases_name;
        System.out.println("Connecting to databases: " + url);

        String user = "charliechen"; // 这个是我自己的数据库用户名
        String passwd = "passwd"; // 换成你自己的

        try{
      
            Connection connection = DriverManager.getConnection(url, user, passwd);
            
            Statement processing_statement = connection.createStatement();
            ResultSet rs = processing_statement.executeQuery("SELECT id, name FROM users");

            while(rs.next()){
            	// 这里我们将会依次得到结果
                int id = rs.getInt("id");
                String name = rs.getString("name");
                System.out.printf("ID: %d Name: %s\n", id, name);
            }

            rs.close();
            processing_statement.close();
            connection.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
```

​	编写完代码，我们的事情是尝试去运行一下

编译：

```bash
mvn compile
[INFO] Scanning for projects...
[INFO] 
[INFO] ----------------------< com.example:jdbc_example >----------------------
[INFO] Building jdbc_example 1.0-SNAPSHOT
[INFO] --------------------------------[ jar ]---------------------------------
[INFO] 
[INFO] --- maven-resources-plugin:3.0.2:resources (default-resources) @ jdbc_example ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] skip non existing resourceDirectory /home/charliechen/javaee/jdbc/jdbc_example/src/main/resources
[INFO] 
[INFO] --- maven-compiler-plugin:3.8.0:compile (default-compile) @ jdbc_example ---
[INFO] Changes detected - recompiling the module!
[INFO] Compiling 1 source file to /home/charliechen/javaee/jdbc/jdbc_example/target/classes
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time:  2.062 s
[INFO] Finished at: 2025-06-25T08:43:00+08:00
[INFO] ------------------------------------------------------------------------
```

​	运行

```bash
mvn exec:java -Dexec.mainClass="com.example.App"
[INFO] Scanning for projects...
[INFO] 
[INFO] ----------------------< com.example:jdbc_example >----------------------
[INFO] Building jdbc_example 1.0-SNAPSHOT
[INFO] --------------------------------[ jar ]---------------------------------
[INFO] 
[INFO] --- exec-maven-plugin:3.5.1:java (default-cli) @ jdbc_example ---
Connecting to databases: jdbc:mariadb://localhost:3306/my_first_db
SLF4J: No SLF4J providers were found.
SLF4J: Defaulting to no-operation (NOP) logger implementation
SLF4J: See https://www.slf4j.org/codes.html#noProviders for further details.
ID: 1 Name: Alice
ID: 2 Name: Bob
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time:  1.071 s
[INFO] Finished at: 2025-06-25T08:41:37+08:00
[INFO] ------------------------------------------------------------------------
```

