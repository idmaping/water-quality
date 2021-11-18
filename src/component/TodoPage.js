import React from 'react';
import '../App.css';
import Form from './Form'
import TodoList from './TodoList';
import UploadImage from './UploadImage'

function TodoPage(props) {
    return (
        <div>
            <h1>To Do</h1>
            <Form></Form>
            <TodoList></TodoList>
            <UploadImage></UploadImage>
        </div>
    );
}

export default TodoPage;