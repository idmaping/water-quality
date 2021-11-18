//minor bug
//mungkin bikin tampilan lagi loading

import React, { useState } from 'react';
import firebase from '../util/firebase'
import SensorPlotLine from '../component/SensorPlotLine'
import SensorPlotBar from '../component/SensorPlotBar'
import { Row, Container, InputGroup, DropdownButton, Dropdown } from 'react-bootstrap';
import DatePicker from 'react-date-picker';


function Graph(props) {

    const [sensorDate, setSensorDate] = useState()
    const [sensorTime, setSensorTime] = useState()
    const [sensorPH, setSensorPH] = useState()
    const [sensorTDS, setSensorTDS] = useState()
    const [sensorDO, setSensorDO] = useState()
    const [sensorEC, setSensorEC] = useState()
    const [sensorORP, setSensorORP] = useState()
    const [sensorTEMP, setSensorTEMP] = useState()
    //const [sensorLon, setSensorLon] = useState()
    //const [sensorLat, setSensorLat] = useState()
    const [sensorWC, setSensorWC] = useState()
    //const [dbList, setDbList] = useState()

    const [idMachine, setIdMachine] = useState('kapal-1')
    const [tanggal, setTanggal] = useState('')
    const [bulan, setBulan] = useState('')
    const [tahun, setTahun] = useState('')

    const [graphDate, setGraphDate] = useState(new Date());
    const [graphSelect, setGraphSelect] = useState(0);

    const handleGraphSelect = (e) => {
        setGraphSelect(e)
    }
    const monthText = ["Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"];

    const filterArr = arr => arr.filter(function (element) {
        return element !== undefined;
    });

    const arrAvg = arr => filterArr(arr).reduce((sum, curr) => sum + Number(curr), 0) / filterArr(arr).length

    //const average = (array) => array.reduce((sum, curr) => sum + Number(curr), 0) / array.length;

    const grafikBulanan = () => {
        const dbRef = firebase.database().ref('dbrt').child(idMachine).child(graphDate.getFullYear()).child(graphDate.getMonth() + 1)
        dbRef.on('value', (snapshot) => {
            const db = snapshot.val()
            const bulananPH = []
            const bulananTDS = []
            const bulananDO = []
            const bulananEC = []
            const bulananORP = []
            const bulananTEMP = []
            const bulananWC = []
            const bulananDate = []
            const bulananTime = []


            for (let id in db) {
                const avgPH = []
                const avgTDS = []
                const avgDO = []
                const avgEC = []
                const avgORP = []
                const avgTEMP = []
                const avgWC = []
                const avgDate = []

                for (let data in db[id]) {
                    //console.log(id,db[id][data].ph)
                    avgPH.push(db[id][data].ph)
                    avgTDS.push(db[id][data].tds)
                    avgDO.push(db[id][data].do)
                    avgEC.push(db[id][data].ec)
                    avgORP.push(db[id][data].orp)
                    avgTEMP.push(db[id][data].temp)
                    avgWC.push(db[id][data].wc)
                    avgDate.push(db[id][data].date)
                    //console.log(data);
                    

                }

                //ratarata(avgPH)
                console.log("lakukan proses rata2 di avg PH terus di push ke var sbnrnya");
                console.log("bulan ke ", id);
                console.log("seluruh", avgPH);
                console.log("rata-rata", arrAvg(avgPH))

                bulananTime.push(id)
                bulananDate.push(avgDate)
                bulananPH.push(arrAvg(avgPH))
                bulananTDS.push(arrAvg(avgTDS))
                bulananDO.push(arrAvg(avgDO))
                bulananEC.push(arrAvg(avgEC))
                bulananORP.push(arrAvg(avgORP))
                bulananTEMP.push(arrAvg(avgTEMP))
                bulananWC.push(arrAvg(avgWC))

                //console.log(bulananDate);

            }
            setSensorDate(bulananDate)

            try {
                var temp = sensorDate[0][0].split("/")
                setTanggal('')
                setBulan(monthText[temp[1] - 1])
                setTahun(temp[2])
                //console.log(temp)
                setSensorTime(bulananTime)
                setSensorPH(bulananPH)
                setSensorTDS(bulananTDS)
                setSensorDO(bulananDO)
                setSensorEC(bulananEC)
                setSensorORP(bulananORP)
                setSensorTEMP(bulananTEMP)
                setSensorWC(bulananWC)
            } catch (e) {
                console.error("Error")
                setTanggal('')
                setBulan("Data")
                setTahun("Tidak Ditemukan")
                setSensorTime([])
                setSensorPH([])
                setSensorTDS([])
                setSensorDO([])
                setSensorEC([])
                setSensorORP([])
                setSensorTEMP([])
                setSensorWC([])
            }


            console.log("Bulanan")
            //console.log(sensorDate);


        })

    }

    const grafikHarian = () => {
        const dbRef = firebase.database().ref('dbrt').child(idMachine).child(graphDate.getFullYear()).child(graphDate.getMonth() + 1).child(graphDate.getDate())
        dbRef.on('value', (snapshot) => {
            const db = snapshot.val()
            //const listDb = []
            const listDate = []
            const listTime = []
            const listPH = []
            const listTDS = []
            const listDO = []
            const listEC = []
            const listORP = []
            const listTEMP = []
            const listWC = []

            for (let id in db) {
                //listDb.push(db[id])
                listDate.push(db[id].date)
                listTime.push(db[id].time)
                listPH.push(db[id].ph)
                listTDS.push(db[id].tds)
                listDO.push(db[id].do)
                listEC.push(db[id].ec)
                listORP.push(db[id].orp)
                listTEMP.push(db[id].temp)
                listWC.push(db[id].wc)
            }
            //setDbList(listDb)

            setSensorDate(listDate)

            try {
                var temp = sensorDate[0].split("/")
                setTanggal(temp[0])
                setBulan(monthText[temp[1] - 1])
                setTahun(temp[2])
                console.log(temp)
                setSensorTime(listTime)
                setSensorPH(listPH)
                setSensorTDS(listTDS)
                setSensorDO(listDO)
                setSensorEC(listEC)
                setSensorORP(listORP)
                setSensorTEMP(listTEMP)
                setSensorWC(listWC)

            } catch (e) {
                console.error("Error")
                setTanggal("")
                setBulan("Data")
                setTahun("Tidak Ditemukan")
                setSensorTime([])
                setSensorPH([])
                setSensorTDS([])
                setSensorDO([])
                setSensorEC([])
                setSensorORP([])
                setSensorTEMP([])
                setSensorWC([])
            }

        })
        console.log("Harian")

    }

    const handleRefresh = async () => {

        graphSelect > 0 ? grafikBulanan() : grafikHarian()

    }

    return (
        <div>
            <Container fluid="md">

                <Row xs={8} md={3} className="justify-content-md-center">
                    <div className="Container" style={{ textAlign: "center" }}>
                        {graphSelect > 0 ? <h1 className="center">Grafik Bulanan</h1> : <h1 className="center">Grafik Harian</h1>}
                        {graphSelect > 0
                            ? <h2 className="center">{`${bulan} ${tahun}`}</h2>
                            : <h2 className="center">{`${tanggal} ${bulan} ${tahun}`}</h2>}
                    </div>
                    <InputGroup className="mb-3">
                        <button type="button" onClick={handleRefresh} className="btn btn-primary">Refresh</button>
                        <DropdownButton
                            variant="secondary"
                            title={graphSelect > 0 ? "Bulanan" : "Harian"}
                            id="input-group-dropdown-1"
                            onSelect={handleGraphSelect}
                        >
                            <Dropdown.Item eventKey="0">Harian</Dropdown.Item>
                            <Dropdown.Item eventKey="1">Bulanan</Dropdown.Item>
                        </DropdownButton>

                        <DatePicker
                            onChange={setGraphDate}
                            value={graphDate}
                            format="d-M-y"
                        />

                    </InputGroup>
                </Row>


                {graphSelect > 0
                    ?
                    (
                        <Row xs={1} md={1} className="g-4 justify-content-md-center">
                            <SensorPlotBar
                                labelname="PH Meter"
                                data={sensorPH}
                                labels={sensorTime}
                                linecolor='232, 104, 252'
                            />
                            <SensorPlotBar
                                labelname="TDS"
                                data={sensorTDS}
                                labels={sensorTime}
                                linecolor='0, 204, 255'
                            />
                            <SensorPlotBar
                                labelname="DO"
                                data={sensorDO}
                                labels={sensorTime}
                                linecolor='168, 51, 204'
                            />
                            <SensorPlotBar
                                labelname="EC"
                                data={sensorEC}
                                labels={sensorTime}
                                linecolor='255, 102, 0'
                            />
                            <SensorPlotBar
                                labelname="ORP"
                                data={sensorORP}
                                labels={sensorTime}
                                linecolor='0, 153, 51'
                            />
                            <SensorPlotBar
                                labelname="Temperatur"
                                data={sensorTEMP}
                                labels={sensorTime}
                                linecolor='153, 153, 255'
                            />
                            <SensorPlotBar
                                labelname="Water Contact"
                                data={sensorWC}
                                labels={sensorTime}
                                linecolor='9, 118, 158'
                            />
                        </Row>
                    )
                    :
                    (
                        <Row xs={1} md={1} className="g-4 justify-content-md-center">
                            <SensorPlotLine
                                labelname="PH Meter"
                                data={sensorPH}
                                labels={sensorTime}
                                linecolor='200, 0, 0'
                            />
                            <SensorPlotLine
                                labelname="TDS"
                                data={sensorTDS}
                                labels={sensorTime}
                                linecolor='100, 76, 102'
                            />
                            <SensorPlotLine
                                labelname="DO"
                                data={sensorDO}
                                labels={sensorTime}
                                linecolor='3, 6, 202'
                            />
                            <SensorPlotLine
                                labelname="EC"
                                data={sensorEC}
                                labels={sensorTime}
                                linecolor='205, 120, 62'
                            />
                            <SensorPlotLine
                                labelname="ORP"
                                data={sensorORP}
                                labels={sensorTime}
                                linecolor='130, 150, 10'
                            />
                            <SensorPlotLine
                                labelname="Temperatur"
                                data={sensorTEMP}
                                labels={sensorTime}
                                linecolor='3, 76, 102'
                            />
                            <SensorPlotLine
                                labelname="Water Contact"
                                data={sensorWC}
                                labels={sensorTime}
                                linecolor='20, 153, 23'
                            />
                        </Row>
                    )
                }


            </Container>
        </div>
    );
}

export default Graph;