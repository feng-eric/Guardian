<template>
  <div id="app">
    <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
    <!-- <HelloWorld msg="Welcome to Your Vue.js App"/> -->
    <div>
      <b-jumbotron header="Guardian" lead="Novel Approach to Firefighter Safety">
        <p>For more information visit website</p>
        <b-button variant="primary" href="#">More Info</b-button>
      </b-jumbotron>
    </div>
    <div class="row">
            <div class="col-sm-6"> <!-- Temperature Column -->
                <div class="card text-white bg-warning mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Temperature</div>
                    <div class="card-body">
                        <h1 id="temperature" style="font-size: 75px;" class="card-title"> {{temperature}}°C</h1>
                        <p class="card-text">Temperature expressed in Celsius degree.</p>
                    </div>
                </div>
            </div>
            <div class="col-sm-6"> <!-- Humidity Column -->
                <div class="card text-white bg-primary mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Humidity</div>
                    <div class="card-body">
                        <h1 id="humidity" style="font-size: 75px;" class="card-title"> {{humidity}}<span>%</span></h1>
                        <p class="card-text">Relative humidity, expressed in percentage.</p>
                    </div>
                </div>
            </div>
    </div>

      <div id="chart">
      <apexchart type=radialBar height=350 :options="temperatureChart.chartOptions" :series="tempSeries[0].data" />
    </div>

  </div>
</template>

<script>
import HelloWorld from './components/HelloWorld.vue'
import firebase from 'firebase'
import {database} from './main'


export default {
  name: 'app',
  components: {
    HelloWorld
  },
  data() {
    return {
      temperature: '',
      humidity: '',
      tempSeries: [{
        name: 'Temperature Chart',
        data: [50]
      }],
      temperatureChart: {
        chartOptions: {
          plotOptions: {
            radialBar: {
              startAngle: -120,
              endAngle: 1,
              dataLabels: {
                name: {
                  fontSize: '16px',
                  color: undefined,
                  offsetY: 120
                },
                value: {
                  offsetY: 76,
                  fontSize: '22px',
                  color: undefined,
                  formatter: function (val) {
                    return val + "°C";
                  }
                }
              }
            }
          },
          fill: {
            type: 'gradient',
            gradient: {
              shade: 'dark',
              shadeIntensity: 0.15,
              inverseColors: false,
              opacityFrom: 1,
              opacityTo: 1,
              stops: [0, 50, 65, 91]
            },
          },
          stroke: {
            dashArray: 4
          },
          labels: ['Median Ratio']
        }
      }
    }
  },

  created() {
    const tempRef = database.ref('dht11').child('temperature')
    const humRef = database.ref('dht11').child('humidity')
    // tempRef.remove();
    // humRef.remove();

    tempRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)
      
      console.log("temperature: " + value);
      this.temperature = value.toString();
      const newData = [parseFloat(value)]
      this.tempSeries = [{
        data: newData
      }]
    });

    humRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)
      
      console.log("humidity: " + value);
      this.humidity = value.toString();
    });

    

  }
};
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
