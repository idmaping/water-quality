import React from 'react';
import { Line } from 'react-chartjs-2';
import { Card } from 'react-bootstrap';

function SensorPlotLine(props) {
  const data = {
    labels: props.labels,
    datasets: [
      {
        label: props.labelname,
        data: props.data,
        fill: false,
        //backgroundColor: 'rgb(75, 192, 192)',
        backgroundColor: `rgb(${props.linecolor})`,
        borderColor: `rgb(${props.linecolor},0.5)`,

        //borderColor: 'rgba(75, 192, 192, 0.7)',
        borderWidth: 3,
        pointStyle: 'circle',
        pointRadius: 1,
        tension: 0.1,
      },
    ],
  }
  
  const options = {
    scales: {
      yAxes: [
        {
          ticks: {
            beginAtZero: true,
          },
        },
      ],
    },
  }

  return (
    <div>
      <Card className="mb-3" style={{ minWidth: "18rem" }}>
        <Line data={data} options={options}/>
      </Card>

    </div>
  );
}

export default SensorPlotLine;