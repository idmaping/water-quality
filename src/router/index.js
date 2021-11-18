import React from 'react';
import {Route, Switch } from 'react-router-dom'

import Home from '../views/Home'
import About from '../views/About'
import Map from '../views/Map'
import Graph from '../views/Graph'
import NotFound from '../views/NotFound'
import OverrideData from '../views/OverrideData'

function Router(props) {
    return (
        <Switch>
            <Route exact path='/' component={Home}/>
            <Route path='/about' component={About}/>
            <Route path='/graph' component={Graph}/>
            <Route path='/map' component={Map}/>  
            <Route path='/INPUTDATA' component={OverrideData}/>  
            <Route path='*' component={NotFound}/>  
        </Switch>

    );
}

export default Router;