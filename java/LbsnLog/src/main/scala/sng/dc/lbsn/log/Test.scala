package sng.dc.lbsn.log

import sng.dc.lbsn.log.GpsLogPb.{PosGpsLog, GpsLog}

object Test {
  def main(args: Array[String]) {
    GpsLog gpsLog = GpsLog.newBuilder().setUin(10l).build()
    println(gpsLog.getUin)
  }
}
