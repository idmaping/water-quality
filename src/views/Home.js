//data belum terkoneksi dg fb


import React, { useEffect, useState } from 'react';
import { Container, Row, Col } from 'react-bootstrap';
import CardSensor from '../component/CardSensor'
import firebase from '../util/firebase'


function Home(props) {

    const [sensorDate, setSensorDate] = useState()
    const [sensorTime, setSensorTime] = useState()
    const [sensorPH, setSensorPH] = useState()
    const [sensorTDS, setSensorTDS] = useState()
    const [sensorDO, setSensorDO] = useState()
    const [sensorEC, setSensorEC] = useState()
    const [sensorORP, setSensorORP] = useState()
    const [sensorTEMP, setSensorTEMP] = useState()
    const [sensorLon, setSensorLon] = useState()
    const [sensorLat, setSensorLat] = useState()
    const [sensorWC, setSensorWC] = useState()
    const [idMachine, setIdMachine] = useState('kapal-1')


    const getFBData = () => {
        const dbRef = firebase.database().ref('last-data').child('kapal-1')
        dbRef.on('value', (snapshot) => {
            const db = snapshot.val()
            setSensorPH(db.ph)
            setSensorTDS(db.tds)
            setSensorDO(db.do)
            setSensorEC(db.ec)
            setSensorORP(db.orp)
            setSensorTEMP(db.temp)
            setSensorLon(db.long)
            setSensorLat(db.lat)
            setSensorDate(db.date)
            setSensorTime(db.time)
            setSensorWC(db.wc)
        })
        
    }
    
    useEffect(() => {
        getFBData()
    }, [])


    return (
        <div>
            <Container fluid="md">
                <Row xs={1} md={2} className="g-4 justify-content-md-center">
                    
                    <Col xs={'auto'} md={4}>
                    <CardSensor
                        title="PH Meter"
                        subtitle="Digunakan untuk mengetahui kadar asam dalam air. Umumnya nilai PH berkisar antara 6-8"
                        value={sensorPH}
                        date={sensorDate}
                        time={sensorTime}
                        fontsize="100px"
                        imgsrc="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2FPHE868FC.jpg?alt=media&token=0679f64a-4385-4ad5-aee4-e911ba75d319"
                    />
                    </Col>

                    <Col xs={'auto'} md={4}>
                    <CardSensor
                        title="TDS"
                        subtitle="Digunakan untuk mengetahui kadar asam dalam air. Umumnya nilai PH berkisar antara 6-8"
                        value={sensorTDS}
                        date={sensorDate}
                        time={sensorTime}
                        fontsize="100px"
                        imgsrc="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2FTDS00CCFF.jpg?alt=media&token=ce9b4833-ff31-4d5f-b8aa-f0de870a11f3"
                    />
                    </Col>

                    <Col xs={'auto'} md={4}>
                    <CardSensor
                        title="DO"
                        subtitle="Digunakan untuk mengetahui kadar asam dalam air. Umumnya nilai PH berkisar antara 6-8"
                        value={sensorDO}
                        date={sensorDate}
                        time={sensorTime}   
                        fontsize="100px"
                        imgsrc="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2FDOB3C20B.jpg?alt=media&token=a8eeb3c4-a64a-42ee-92eb-9bcfa9226b2b"
                    />
                    </Col>

                    <Col xs={'auto'} md={4}>
                    <CardSensor
                        title="EC"
                        subtitle="Digunakan untuk mengetahui kadar asam dalam air. Umumnya nilai PH berkisar antara 6-8"
                        value={sensorEC}
                        date={sensorDate}
                        time={sensorTime}  
                        fontsize="100px"
                        imgsrc="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2FECFF6600.jpg?alt=media&token=8c36b3bb-2187-4aec-8a81-045bff04ddae"
                    />
                    </Col>

                    <Col xs={'auto'} md={4}>
                    <CardSensor
                        title="ORP"
                        subtitle="Digunakan untuk mengetahui kadar asam dalam air. Umumnya nilai PH berkisar antara 6-8"
                        value={sensorORP}
                        date={sensorDate}
                        time={sensorTime}     
                        fontsize="100px"
                        imgsrc="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2FORP009933.jpg?alt=media&token=2e406356-7cfa-462d-b1ef-1bc5d2c9938a" 
                    />
                    </Col>

                    <Col xs={'auto'} md={4}>
                    <CardSensor
                        title="Temperatur"
                        subtitle="Digunakan untuk mengetahui kadar asam dalam air. Umumnya nilai PH berkisar antara 6-8"
                        value={sensorTEMP}
                        date={sensorDate}
                        time={sensorTime}  
                        fontsize="100px"
                        imgsrc="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2FTEMPERATURE9999FF.jpg?alt=media&token=e8c5e42b-f578-4c68-bfcc-ebc49e48f799"
                    />
                    </Col>

                    <Col xs={'auto'} md={4}>
                    <CardSensor
                        title="Water Contact"
                        subtitle="Digunakan untuk mengetahui kadar asam dalam air. Umumnya nilai PH berkisar antara 6-8"
                        value={sensorWC}
                        date={sensorDate}
                        time={sensorTime}    
                        fontsize="100px"
                        imgsrc="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2FWATERCONTACT09769E.jpg?alt=media&token=d50ff460-ad85-496a-9c56-cba0de56e6af"
                    />
                    </Col>

                    <Col xs={'auto'} md={4}>
                    <CardSensor
                        title="Latitude"
                        subtitle="Digunakan untuk mengetahui kadar asam dalam air. Umumnya nilai PH berkisar antara 6-8"
                        value={sensorLat}
                        date={sensorDate}
                        time={sensorTime}    
                        fontsize="60px"
                        imgsrc="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2FLAT805E44.jpg?alt=media&token=cebaa623-160e-4599-a7c3-93db7b5f65f6"
                    />
                    </Col>

                    <Col xs={'auto'} md={4}>
                    <CardSensor
                        title="Longitude"
                        subtitle="Digunakan untuk mengetahui kadar asam dalam air. Umumnya nilai PH berkisar antara 6-8"
                        value={sensorLon}
                        date={sensorDate}
                        time={sensorTime}  
                        fontsize="60px"
                        imgsrc="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2FLONGE83F3C.jpg?alt=media&token=05b4c906-2466-4c34-af0a-8547e8eaf9fd" 
                    />
                    </Col>
                </Row>
            </Container>
        </div>


    );
}



export default Home;