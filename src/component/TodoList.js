import React, { useEffect, useState } from 'react';
import firebase from '../util/firebase'
import Todo from './Todo'


function TodoList(props) {
    const [todoList,setTodoList] = useState()


    useEffect(() => {
        const todoRef = firebase.database().ref('Todo')
        todoRef.on('value',(snapshot) => {
            const todos = snapshot.val()
            const todoList = []
            for (let id in todos){
                todoList.push({id, ...todos[id]})
            }
            console.log(todoList);
            setTodoList(todoList)
        })
    }, [])

    return (
        <div>
            <h1>TodoList</h1>

            { todoList
            ? todoList.map((todo, index) => <Todo todo={todo} key={index} />)
            : '' }

        </div>
    );
}

export default TodoList;