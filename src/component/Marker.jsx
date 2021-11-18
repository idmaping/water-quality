import React from 'react';
import './Marker.css';

const Marker = (props) => {
  const { color, name, id } = props;
  return (
    <div>
      <div
        className="pin bounce"
        style={{ backgroundColor: color, cursor: 'pointer' }}
        title={name}
      />
      <div className="pulse" />
      <br/>
      <p>
        <font size="4"
          face="arial"
          color={color}>
          {name}
        </font>
      </p>
    </div>
  );
};

export default Marker;