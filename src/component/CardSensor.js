import React from 'react';
//import { NavLink } from 'react-router-dom';
import { Card } from 'react-bootstrap';

function CardSensor(props) {
    return (
        <div>

            <Card className="mb-3" style={{ minWidth: "18rem" }}>
                <Card.Img src={props.imgsrc} alt="Card image" />
                <Card.ImgOverlay className="text-center">
                    <Card.Title>
                        <p style={{ fontSize: props.fontsize, display: "flex", justifyContent: "center", textAlign: "bottom" }}>
                            {props.value}
                        </p>
                    </Card.Title>
                </Card.ImgOverlay>
                <Card.Body>
                    <Card.Title>{props.title}</Card.Title>
                    <Card.Text>
                        {props.subtitle}
                    </Card.Text>
                    
                </Card.Body>
                <Card.Footer>
                    <small className="text-muted">{`Terakhir di update : ${props.date} ${props.time}`}</small>
                </Card.Footer>
            </Card>

            {/*

            <div class="card mb-3" style={{minWidth: "18rem" }}>
                <div class="row g-0">
                    <div class="col-md-4">
                        <img src="https://cdn.iconscout.com/icon/premium/png-512-thumb/ph-balanced-1916308-1624203.png" class="img-fluid rounded-start" alt="..."/>
                    </div>
                        <div class="col-md-8">
                            <div class="card-body">
                                <h5 class="card-title">Card title</h5>
                                <p class="card-text">This is a wider card with supporting text below as a natural lead-in to additional content. This content is a little bit longer.</p>
                                <p class="card-text"><small class="text-muted">Last updated 3 mins ago</small></p>
                            </div>
                        </div>
                    </div>
                </div>
            
            <Card style={{ minWidth: "18rem" }}>
                <Card.Img src="https://cdn.iconscout.com/icon/premium/png-512-thumb/ph-balanced-1916308-1624203.png" alt="Card image" />
                <Card.ImgOverlay className="text-center">
                    <Card.Title>
                        <p style={{ fontSize: "8rem", display: "flex", justifyContent: "center", textAlign: "bottom" }}>
                            {props.value}
                        </p>
                    </Card.Title>
                </Card.ImgOverlay>
                <Card.Body>
                    <Card.Title>{props.title}</Card.Title>
                    <Card.Text>
                        {props.subtitle}
                    </Card.Text>
                    <a href="#" class="btn btn-primary stretched-link">Lihat Grafik</a>
                </Card.Body>
                <Card.Footer>
                    <small className="text-muted">{`Terakhir di update : ${props.date} ${props.time}`}</small>
                </Card.Footer>
            </Card>

            */}

        </div>
    );
}

export default CardSensor;