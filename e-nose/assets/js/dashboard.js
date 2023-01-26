/* globals Chart:false, feather:false */

(function () {
  'use strict'

  feather.replace()

  // Graphs
  var ctx = document.getElementById('myChart')
  // eslint-disable-next-line no-unused-vars
  const labels = [
    'Sunday',
    'Monday',
    'Tuesday',
    'Wednesday',
    'Thursday',
    'Friday',
    'Saturday'
  ];
  const data = {
    labels: labels,
    datasets: [
      {
        label: 'Dataset 1',
        data:  [
          15339,
          21345,
          18483,
          24003,
          23489,
          24092,
          12034
        ],
        borderColor: 'rgb(75, 192, 192)',
        yAxisID: 'y',
      },
      {
        label: 'Dataset 2',
        data:  [
          12344,
          22112,
          22312,
          23412,
          23121,
          23212,
          23123
        ],
        borderColor: 'rgb(154, 208, 245)',
        yAxisID: 'y1',
      }
    ]
  };

  var myChart = new Chart(ctx, {
    type: 'line',
    data: data,
    options: {
      responsive: true,
      interaction: {
        mode: 'index',
        intersect: false,
      },
      stacked: false,
      plugins: {
        title: {
          display: true,
          text: 'Chart.js Line Chart - Multi Axis'
        }
      },
      scales: {
        y: {
          type: 'linear',
          display: true,
          position: 'left',
        },
        y1: {
          type: 'linear',
          display: true,
          position: 'right',
  
          // grid line settings
          grid: {
            drawOnChartArea: false, // only want the grid lines for one axis to show up
          },
        },
      }
    },
  });
})()
