import React from 'react';
import { NavLink } from 'react-router-dom';

function Navbar(props) {
    return (
        <div>
            <nav className="navbar navbar-expand-lg navbar-dark bg-dark">
                <div className="container-fluid">
                    <NavLink className="navbar-brand" to="/">
                        <img src="https://firebasestorage.googleapis.com/v0/b/sambigede.appspot.com/o/webimages%2Ficon-roboat-ndas.png?alt=media&token=a05e6953-2438-4eab-8e18-2c1acf36272a" 
                             alt="" width="30" height="30" className="d-inline-block align-text-top"/>
                        &nbsp; Ro-Boat
                    </NavLink>
                    <button className="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
                        <span className="navbar-toggler-icon"></span>
                    </button>
                    <div className="collapse navbar-collapse" id="navbarNavAltMarkup">
                        <div className="navbar-nav">
                            <NavLink exact className="nav-link" aria-current="page" to="/">Beranda</NavLink>
                            <NavLink className="nav-link" to="/graph">Grafik</NavLink>
                            <NavLink className="nav-link" to="/map">Peta Sebaran</NavLink>
                            <NavLink className="nav-link" to="/about">Tentang</NavLink>                            
                        </div>
                    </div>
                </div>
            </nav>
        </div>
    );
}

export default Navbar;