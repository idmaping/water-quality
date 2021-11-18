import React, { useEffect, useState } from 'react';
import SensorPlot from './component/SensorPlot'
import InputDummyDatabase from './component/InputDummyDatabase'
import firebase from './util/firebase'

function App(props) {

  const [sensorDate, setSensorDate] = useState()
  const [sensorTime, setSensorTime] = useState()
  const [sensorPH, setSensorPH] = useState()
  const [sensorTDS, setSensorTDS] = useState()
  const [sensorDO, setSensorDO] = useState()
  const [sensorEC, setSensorEC] = useState()
  const [sensorORC, setSensorORC] = useState()
  const [sensorTEMP, setSensorTEMP] = useState()
  const [sensorLon, setSensorLon] = useState()
  const [sensorLat, setSensorLat] = useState()
  const [dbList, setDbList] = useState()

  useEffect(() => {
    const dbRef = firebase.database().ref('realtime-db')
    dbRef.on('value', (snapshot) => {
      const db = snapshot.val()
      const listDate = []
      const listTime = []
      const listPH = []
      const listTDS = []
      const listDO = []
      const listEC = []
      const listORC = []
      const listTEMP = []
      const listLon = []
      const listLat = []
      const listDb = []
      for (let id in db) {
        listDate.push(db[id].date)
        listTime.push(db[id].time)
        listPH.push(db[id].ph)
        listTDS.push(db[id].tds)
        listDO.push(db[id].do)
        listEC.push(db[id].ec)
        listORC.push(db[id].orc)
        listTEMP.push(db[id].temp)
        listLon.push(db[id].lon)
        listLat.push(db[id].lat)
        listDb.push(db[id])
      }
      setSensorDate(listDate)
      setSensorTime(listTime)
      setSensorPH(listPH)
      setSensorTDS(listTDS)
      setSensorDO(listDO)
      setSensorEC(listEC)
      setSensorORC(listORC)
      setSensorTEMP(listTEMP)
      setSensorLon(listLon)
      setSensorLat(listLat)
      setDbList(listDb)

    })
  }, [])

  return (
    <div>
      <div className="p-5">
        <div className="container">
          
          <SensorPlot
            labelname = "PH"
            data = {sensorPH}
            labels = {sensorTime}
            linecolor = '200, 0, 0'
          />

          <SensorPlot
            labelname = "DO"
            data = {sensorDO}
            labels = {sensorTime}
            linecolor = '3, 76, 102'
          />

        </div>
      </div>



    </div>
  );
}

export default App;