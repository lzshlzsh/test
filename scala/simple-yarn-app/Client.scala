package mytest.scala

import scala.collection.JavaConversions.{mapAsJavaMap, seqAsJavaList}

import org.apache.hadoop.conf.Configuration
import org.apache.hadoop.fs.FileStatus
import org.apache.hadoop.fs.FileSystem
import org.apache.hadoop.fs.Path
import org.apache.hadoop.yarn.api.ApplicationConstants
import org.apache.hadoop.yarn.api.ApplicationConstants.Environment
import org.apache.hadoop.yarn.api.records.ApplicationId
import org.apache.hadoop.yarn.api.records.ApplicationReport
import org.apache.hadoop.yarn.api.records.ApplicationSubmissionContext
import org.apache.hadoop.yarn.api.records.ContainerLaunchContext
import org.apache.hadoop.yarn.api.records.LocalResource
import org.apache.hadoop.yarn.api.records.LocalResourceType
import org.apache.hadoop.yarn.api.records.LocalResourceVisibility
import org.apache.hadoop.yarn.api.records.Resource
import org.apache.hadoop.yarn.api.records.YarnApplicationState
import org.apache.hadoop.yarn.client.api.YarnClient
import org.apache.hadoop.yarn.client.api.YarnClientApplication
import org.apache.hadoop.yarn.conf.YarnConfiguration
import org.apache.hadoop.yarn.util.Apps
import org.apache.hadoop.yarn.util.ConverterUtils
import org.apache.hadoop.yarn.util.Records

object Client {
  def main(args: Array[String]) {
    if (args.length != 3) {
      println("Usage: Client command n jars")
      println("e.g Client date 2 simple_yarn_app.jar")
      System.exit(-1)
    }
    
    val command = args(0)
    val executors = args(1).toInt
    val jars = args(2)
    
    run(command, executors, jars)
  }

  private def run(command: String, executors: Int, jars: String) {
    // Create yarnClient
    val conf = new YarnConfiguration()
    val yarnClient = YarnClient.createYarnClient()
    yarnClient.init(conf)
    yarnClient.start()

    // Create application via yarnClient
    val app = yarnClient.createApplication()

    // Set up the container launch context for the application master
    val amContainer = Records.newRecord(classOf[ContainerLaunchContext])
    amContainer.setCommands(
      List(
        "$JAVA_HOME/bin/java" +
        " -Xmx256M" +
        " mytest.scala.ApplicationMaster" +
        " " + command +
        " " + executors +
        " 1>" + ApplicationConstants.LOG_DIR_EXPANSION_VAR + "/stdout" + 
        " 2>" + ApplicationConstants.LOG_DIR_EXPANSION_VAR + "/stderr" 
        )
      )

    // Setup jar for ApplicationMaster
    val appMasterJar = Records.newRecord(classOf[LocalResource])
    setupAppMasterJar(jars, conf, appMasterJar)
    amContainer.setLocalResources(Map("simpleapp.jar" -> appMasterJar))

    // Setup CLASSPATH for ApplicationMaster
    val appMasterEnv = Map[String, String]()
    setupAppMasterEnv(appMasterEnv)
    amContainer.setEnvironment(appMasterEnv)

    // Set up resource type requirements for ApplicationMaster
    val capability = Records.newRecord(classOf[Resource])
    capability.setMemory(256)
    capability.setVirtualCores(1)

    // Finally, set-up ApplicationSubmissionContext for the application
    val appContext = app.getApplicationSubmissionContext()
    appContext.setApplicationName("simple-yarn-app") // application name
    appContext.setAMContainerSpec(amContainer)
    appContext.setResource(capability)
    appContext.setQueue("default") // queue 

    // Submit application
    val appId = appContext.getApplicationId()
    println("Submitting application " + appId)
    yarnClient.submitApplication(appContext)

    var appReport = yarnClient.getApplicationReport(appId)
    var appState = appReport.getYarnApplicationState()
    while (appState != YarnApplicationState.FINISHED && 
           appState != YarnApplicationState.KILLED && 
           appState != YarnApplicationState.FAILED) {
      Thread.sleep(100)
      appReport = yarnClient.getApplicationReport(appId)
      appState = appReport.getYarnApplicationState()
    }
    
    println(
        "Application " + appId + " finished with" +
        " state " + appState + 
        " at " + appReport.getFinishTime());
  }
  private def setupAppMasterJar(jars: String, conf: YarnConfiguration, appMasterJar: LocalResource) {
    val t: java.lang.String = "aa"
    val jarPath = new Path(t)
    val jarStat = FileSystem.get(conf).getFileStatus(jarPath)
    appMasterJar.setResource(ConverterUtils.getYarnUrlFromPath(jarPath))
    appMasterJar.setSize(jarStat.getLen())
    appMasterJar.setTimestamp(jarStat.getModificationTime())
    appMasterJar.setType(LocalResourceType.FILE)
    appMasterJar.setVisibility(LocalResourceVisibility.PUBLIC)
  }
  private def setupAppMasterEnv(appMasterEnv: Map[String, String]) {
  }
  }
