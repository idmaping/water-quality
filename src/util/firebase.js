import firebase from 'firebase/compat/app'
import 'firebase/compat/database'
import 'firebase/compat/storage'



const firebaseConfig = {

  apiKey: "AIzaSyAYuG98AgYncr0f2yxRi9fh6fcsY1ill3M",

  authDomain: "water-quality-763c8.firebaseapp.com",

  databaseURL: "https://water-quality-763c8-default-rtdb.asia-southeast1.firebasedatabase.app",

  projectId: "water-quality-763c8",

  storageBucket: "water-quality-763c8.appspot.com",

  messagingSenderId: "315322872290",

  appId: "1:315322872290:web:17f77f70364c98990209bb",

  measurementId: "G-EQ9ZGC5TXZ"

};


  

firebase.initializeApp(firebaseConfig)

export default firebase
