import Vue from 'vue'
import { firestorePlugin } from 'vuefire'
import App from './App.vue'

import firebase from 'firebase'
// import ApexCharts from 'apexcharts'
// import VueApexCharts from 'vue-apexcharts'
import ApexCharts from 'apexcharts'
import VueApexCharts from 'vue-apexcharts'
// import Vue from 'vue'
import { ToggleButton } from 'vue-js-toggle-button'
import BootstrapVue from 'bootstrap-vue';
import 'bootstrap/dist/css/bootstrap.css'
import 'bootstrap-vue/dist/bootstrap-vue.css'

Vue.component('ToggleButton', ToggleButton)
Vue.component('apexchart', VueApexCharts);
Vue.config.productionTip = false
Vue.use(BootstrapVue)
Vue.use(firestorePlugin)
// Vue.component('apexchart', VueApexCharts)
let firebaseConfig = {
  apiKey: "AIzaSyAr4XfjXnQ0MDKF8ItJF5g0_sfOJym5QdE",
  authDomain: "guardian-8888.firebaseapp.com",
  databaseURL: "https://guardian-8888.firebaseio.com",
  projectId: "guardian-8888",
  storageBucket: "",
  messagingSenderId: "479861968929",
  appId: "1:479861968929:web:e7f9b6edbc21d8f1941360"
};

firebase.initializeApp(firebaseConfig);

export var database = firebase.database();
new Vue({
  render: h => h(App),
  // data: function() {
  //   return {
  //     options: {
  //       chart: {
  //         id: 'vuechart-example'
  //       },
  //       xaxis: {
  //         categories: [1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998]
  //       }
  //     },
  //     series: [{
  //       name: 'series-1',
  //       data: [30, 40, 45, 50, 49, 60, 70, 91]
  //     }]
  //   }
  // }
}).$mount('#app')
