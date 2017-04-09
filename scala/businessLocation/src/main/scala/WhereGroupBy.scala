import org.apache.spark.sql.{SQLContext, _}
import org.apache.spark.sql.types._
import org.apache.spark.{SparkConf, SparkContext}

/**
 * Created by lzs on 3/23/15.
 */

object WhereGroupBy {
  def main(args: Array[String]) {
    if (args.length != 1) {
      System.err.println("Usage: WhereGroupBy <input>")
      System.exit(-1)
    }
    val sc = new SparkContext(new SparkConf())
    val sqlContext = new SQLContext(sc)

    val schema = StructType(
      Array(
        StructField("id", StringType, false),
        StructField("uin", LongType, false),
        StructField("comId", IntegerType, false)
      )
    )
    val input = args(0)

    val community = sc.textFile(input).map(_.split("\t")).map(p =>
      Row(p(0), p(1).toLong, p(2).toInt))

    val dataFrame = sqlContext.createDataFrame(community, schema)
    dataFrame.printSchema()

    dataFrame.persist(org.apache.spark.storage.StorageLevel.OFF_HEAP)

    dataFrame.registerTempTable("WhereGroupBy")
    sqlContext.sql("select id,count(1) from WhereGroupBy group by id").count()
    sqlContext.sql("select id,count(1) from WhereGroupBy group by id").count()

    sc.stop()
  }
}
