//data belum terkoneksi dg fb

import GoogleMapReact from 'google-map-react';
import React, { useEffect, useState } from 'react';
import { Container, Row } from 'react-bootstrap';
import Marker from '../component/Marker';
import firebase from '../util/firebase'

function Map(props) {

    const [sensorLon, setSensorLon] = useState(0)
    const [sensorLat, setSensorLat] = useState(0)
    const [idMachine, setIdMachine] = useState('kapal-1')
    
    const getFBData = () => {
        const dbRef = firebase.database().ref('last-data').child(idMachine)
        dbRef.on('value', (snapshot) => {
            const db = snapshot.val()
            setSensorLon(db.long)
            setSensorLat(db.lat)
        })   
    }

    useEffect(() => {
        getFBData()
        console.log(sensorLat,sensorLon);
    }, [])


    return (
        <div>
            <Container fluid="md">
                <Row xs={1} md={1} className="justify-content-md-center">
                    <div className="Container" style={{ textAlign: "center" }}>
                        <h1>Peta Sebaran</h1>
                        <div style={{ height: '78vh', width: '100%' }}>
                            <GoogleMapReact
                                //bootstrapURLKeys={{ key: /* YOUR KEY HERE */ }}
                                defaultCenter={{ lat: -8.1847278, lng: 112.48847 }}
                                defaultZoom={14}
                            >
                                <Marker lat={sensorLat} lng={sensorLon} name="Kapal_1" color="red"/>
                            </GoogleMapReact>
                        </div>
                    </div>
                </Row>
            </Container>
        </div >
    );
}

export default Map;