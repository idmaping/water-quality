import React from 'react';
import firebase from '../util/firebase'
import '../App.css'

function Todo({todo}) {


    const handleDelete = () => {
        const todoRef = firebase.database().ref('Todo').child(todo.id)
        todoRef.remove()
      }

    const handleComplete = () => {
        const todoRef = firebase.database().ref('Todo').child(todo.id);
        todoRef.update({
            complete: !todo.complete,
        })
    }


    return (
        <div>
            <h1 className={todo.complete ? 'complete' : ''}>{todo.title}</h1>
            <button onClick={handleDelete}>Delete</button>
            <button onClick={handleComplete}>Complete</button>
        </div>
    );
}

export default Todo;