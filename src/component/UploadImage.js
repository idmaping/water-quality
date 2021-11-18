import React, { useEffect, useState } from 'react';
import firebase from '../util/firebase'
import {v4 as uuid} from 'uuid'

function UploadImage(props) {
    const [imageUrl,setImageUrl] = useState([])

    const readImage = async(e) => {
        const file = e.target.files[0]
        const id = uuid()
        const storageRef = firebase.storage().ref('images').child(id)
        const imageRef = firebase.database().ref('images').child('daily').child(id)
        await storageRef.put(file)
        storageRef.getDownloadURL().then((url) => {
            imageRef.set(url)
            const newState = [...imageUrl,{id, url}]
            setImageUrl(newState)
        })
    }

    const getImageUrl = () => {
        const imageRef = firebase.database().ref('images').child('daily')
        imageRef.on('value',(snapshot) =>{
            const imageUrls = snapshot.val()
            const urls = []
            for (let id in imageUrls){
                urls.push({id,url: imageUrls[id]})
            }
            const newState = [...imageUrl, ...urls]
            setImageUrl(newState)
        })
    }

    const deleteImage = (id) => {
        const storageRef = firebase.storage().ref('images').child(id)
        const imageRef = firebase.database().ref('images').child('daily').child(id)
        storageRef.delete().then(() =>{
            imageRef.remove()
        })
    }

    useEffect(() => {
        getImageUrl()
    },[])

    return (
        <div>
            <h1>Upload Image</h1>
            <input type="file" accept="image/*" onChange={readImage}></input>
            {imageUrl
                ? imageUrl.map(({id,url}) => {
                    return (
                        <div key={id}>
                            <img src={url} alt=""/>
                            <button onClick={() => deleteImage(id)}>Delete</button>
                        </div>
                    )
                })
                : ''

            }
        </div>
    );
}

export default UploadImage;