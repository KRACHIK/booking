#include "qt_create_calandar.h"

QString timeInterval(const QString& from, const QString& to, const QString& format = "dd.MM.yyyy")
{
  QDateTime fromDt = QDateTime::fromString(from, format);
  QDateTime toDt = QDateTime::fromString(to, format);
  if (fromDt.isValid() && toDt.isValid()) {
    QDateTime interval = QDateTime::fromMSecsSinceEpoch(toDt.toMSecsSinceEpoch() - fromDt.toMSecsSinceEpoch());
    interval = interval.addYears(-1970);
    return interval.toString(format);
  }
  return QString::null;
}

void CGetApart::init()
{
    qDebug () << timeInterval("01.01.2010", "25.01.2010"  ) << "\n"; //HZ
    qDebug () << timeInterval("01.01.2010", "25.02.2010"  ) << "\n"; //HZ



    CUniqKey  UniqKey;

    std::vector<CHomeNameAndCostAndData> Aparts =  CUniqKeydbManager::sql_select(UniqKey,
     //"AlpinaHotel_https://r-cf.bstatic.com/xdata/images/hotel/square200/233703169.jpg?k=06b920fb70ba9014be03ba225e21277da7aef7275c3550a0394d475787d42290&o="
      "GudauriDacha-Too_https://q-cf.bstatic.com/xdata/images/hotel/square200/185517141.jpg?k=9793411cfb58722e774d855e4ac3cb1b0c917fcdc5da1e2bdea0224bc3250e2e&o="
                                                                                 );

    CHotelManager  HotelManager;

    for(CHomeNameAndCostAndData it : Aparts)
    {
        HotelManager.push_back(it);
    }
    HotelManager.Compute();

    qDebug() << "[CGetApart::init] : get_count_day_svoboden_dl9_zaseleniya: "<< HotelManager.get_count_day_svoboden_dl9_zaseleniya();

    HotelManager.save_result_compute("del-test.txt");

}
