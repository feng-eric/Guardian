import Vue from 'vue'
import { firestorePlugin } from 'vuefire'
import App from './App.vue'

import BootstrapVue from 'bootstrap-vue'


import firebase from 'firebase'

import VueApexCharts from 'vue-apexcharts'
Vue.use(BootstrapVue)
Vue.component('apexchart', VueApexCharts)

Vue.config.productionTip = false

Vue.use(firestorePlugin)

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
}).$mount('#app')
