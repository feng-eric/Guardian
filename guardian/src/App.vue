<template>
  <div id="app">
    <div>
      <b-jumbotron header="Guardian" lead="Novel Approach to Firefighter Safety">
        <img src="https://image.flaticon.com/icons/svg/206/206877.svg" height="200px"></img>
        <!-- <p>For more information visit website</p>
        <b-button variant="primary" href="#">More Info</b-button> -->
      </b-jumbotron>
    </div>
    <div class="row">
            <div class="col-sm-6"> <!-- Temperature Column -->
                <div class="card text-white bg-warning mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Temperature</div>
                    <ToggleButton 
                      @change="toggleTemperature"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showTemperature">
                      <!-- <div @click=toggleTemperature>
                        Click to see chart
                      </div>   -->
                      <div class="card-body">
                          <h1 id="temperature" style="font-size: 75px;" class="card-title"> {{temperature}}°C</h1>
                          <p class="card-text">Temperature expressed in Celsius degree.</p>
                      </div>
                    </div>
                    <div v-else>
                      <!-- <div @click=toggleTemperature>
                        Click to see current data
                      </div>   -->
                      <apexchart width="500" type="line" :options="options" :series="series"></apexchart>
                    </div>
                </div>
            </div>
            <div class="col-sm-6"> <!-- Humidity Column -->
                <div class="card text-white bg-primary mb-3" style="max-width: 18rem;">
                    <div style="font-size: 20px;" class="card-header">Humidity</div>
                     <ToggleButton 
                      @change="toggleHumidity"
                      :width="toggleButtonWidth"
                      :labels="{checked: 'Chart', unchecked: 'Current Data'}"/>
                    <div v-if="showHumidity">
                      <div class="card-body">
                          <h1 id="humidity" style="font-size: 75px;" class="card-title"> {{humidity}}<span>%</span></h1>
                          <p class="card-text">Relative humidity, expressed in percentage.</p>
                      </div>
                    </div>
                    <div v-else>
                      <apexchart width="500" type="line" :options="options" :series="series"></apexchart>
                    </div>
                </div>
            </div>
            <div id="chart">
              <!--  -->
              <apexchart ref="realtimeChart" type=line height=400 width=500 :options="options" :series="series" />
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
    HelloWorld,
    // 'apexchart': ApexCharts
  },
  data() {
    return {
      temperatureData: [],
      showTemperature: true,
      showHumidity: true,
      temperature: '',
      humidity: '',
      toggleButtonWidth: 100,
      options: {
        chart: {
          id: 'vuechart-example'
        },
        xaxis: {
          // categories: [1,2, 3, 4, 5, 6, 7, 8]
        }
      },
      series: [{
        name: 'series-1',
        data: [34, 53]
      }],
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
    //tempRef.remove();
    //humRef.remove();

    tempRef.limitToLast(1).on('value', querySnapshot => {
      let data = querySnapshot.val();
      let value = Object.values(data)
      console.log(value.toString())
      console.log("temp array before")
      console.log(this.temperatureData)
      console.log("temp array after")
      // this.temperatureData.push(value.toString())
      console.log(this.temperatureData)
      var date = new Date()
      var hours = date.getHours()
      var minutes = date.getMinutes()
      var seconds = date.getSeconds()
      if (seconds < 10) {
        seconds = "0" + seconds.toString()
      }
      var time = hours + ":" + minutes + ":" + seconds
      this.temperatureData.push({ x : time, y : value.toString()})
      if (this.temperatureData.length > 8) {
        this.temperatureData = this.temperatureData.slice(this.temperatureData.length - 8, this.temperatureData.length)
      }
      this.$refs.realtimeChart.updateSeries([{
        data: this.temperatureData
      }])
      // getNewSeries(lastDate, {
      //   min: 20,
      //   max: 90
      // })
      // chart.updateSeries([{
      //   data: value
      // }])
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

    

  },
  methods: {
    toggleTemperature(){
      console.log(this.showTemperature)
      this.showTemperature = !this.showTemperature;
    },
    toggleHumidity(){
      console.log(this.showHumidity)
      this.showHumidity = !this.showHumidity;
    }
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
