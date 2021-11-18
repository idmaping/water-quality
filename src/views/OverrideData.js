import React, { useState } from 'react';
import firebase from '../util/firebase';

function OverrideData(props) {

    const [sensorDate,    setSensorDate]   = useState('')
    const [sensorTime,    setSensorTime]   = useState('')
    const [sensorPH,    setSensorPH]   = useState()
    const [sensorTDS,   setSensorTDS]  = useState()
    const [sensorDO,    setSensorDO]   = useState()
    const [sensorEC,    setSensorEC]   = useState()
    const [sensorORP,   setSensorORP]  = useState()
    const [sensorTEMP,  setSensorTEMP] = useState()
    const [sensorWC,  setSensorWC] = useState()
    const [sensorLon,  setSensorLon] = useState()
    const [sensorLat,  setSensorLat] = useState()
    
    const handleOnClick = () => {
        //bagian ini untuk update
        const kirimRef = firebase.database().ref(`dbrt/kapal-1/${sensorDate}`)
        const data  = {
            time:sensorTime,
            date:sensorDate,
            ph:sensorPH,
            tds:sensorTDS,
            do:sensorDO,
            ec:sensorEC,
            orp:sensorORP,
            temp:sensorTEMP,
            wc:sensorWC,
            long:sensorLon,
            lat:sensorLat,
        }
        kirimRef.push(data)
        //=======================
    }

    return (
        <div className="py-4">
            <div className="container">
                <div className="md-4">
                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input DO</span>
                    <input type="text" className="form-control" value={sensorDO} onChange={(e) => setSensorDO(e.target.value)}/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input EC</span>
                    <input type="text" className="form-control" value={sensorEC} onChange={(e) => setSensorEC(e.target.value)}/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input ORP</span>
                    <input type="text" className="form-control" value={sensorORP} onChange={(e) => setSensorORP(e.target.value)}/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input PH</span>
                    <input type="text" className="form-control" value={sensorPH} onChange={(e) => setSensorPH(e.target.value)}/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input TDS</span>
                    <input type="text" className="form-control" value={sensorTDS} onChange={(e) => setSensorTDS(e.target.value)}/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input Temp</span>
                    <input type="text" className="form-control" value={sensorTEMP} onChange={(e) => setSensorTEMP(e.target.value)}/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input WC</span>
                    <input type="text" className="form-control" value={sensorWC} onChange={(e) => setSensorWC(e.target.value)}/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input Latitude</span>
                    <input type="text" className="form-control" value={sensorLat} onChange={(e) => setSensorLat(e.target.value)}/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input Longitude</span>
                    <input type="text" className="form-control" value={sensorLon} onChange={(e) => setSensorLon(e.target.value)}/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input Time</span>
                    <input type="text" className="form-control" value={sensorTime} onChange={(e) => setSensorTime(e.target.value)} placeholder="jj.mm"/>
                </div>

                <div class="input-group input-group-lg">
                    <span class="input-group-text" id="inputGroup-sizing-lg">Input Date</span>
                    <input type="text" className="form-control" value={sensorDate} onChange={(e) => setSensorDate(e.target.value)} placeholder="yyyy/mm/dd"/>
                </div>

                <button type="button" onClick={handleOnClick} class="btn btn-primary btn-lg">Submit</button>
                </div>

            </div>

        </div>
    );
}

export default OverrideData;