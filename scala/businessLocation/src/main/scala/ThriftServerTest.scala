/**
 * Created by lzs on 3/24/15.
 */

import java.sql.DriverManager

object ThriftServerTest {
  def main(args: Array[String]) {
    try {
      Class.forName("org.apache.hive.jdbc.HiveDriver")
    } catch {
      case e: ClassNotFoundException =>
        e.printStackTrace()
        System.exit(-1)
    }

    val conn = DriverManager.getConnection("jdbc:hive2://sparkb5-86:10000", "hive", "hive")
    val statement = conn.createStatement()
    val sql = "select id,count(1) from community group by id limit 10"
    println(s"running $sql")
    val result = statement.executeQuery(sql)
    while (result.next()) {
      println(result.getString(1) + "\t" + result.getInt(2))
    }
  }
}
