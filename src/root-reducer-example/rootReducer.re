/* types */
type itemStatus =
  | Done(string)
  | Open;

type todoListItem = {
  id: int,
  itemName: string,
  itemStatus,
};

/* state */
type state = {
  idCounter: int,
  todolist: list(todoListItem),
  newItem: todoListItem,
  modalVisible: bool,
};

/* actions */
type actions =
  | UpdateNewItem(string)
  | DeleteItem(int)
  | AddNewItem
  | CloseItem(int)
  | OpenModal(todoListItem)
  | CloseModal;

let initialNewItem: todoListItem = {id: 0, itemName: "", itemStatus: Open};

let initialState = {
  idCounter: 0,
  todolist: [],
  newItem: initialNewItem,
  modalVisible: false,
};

let rootReducer = (state, action) =>
  switch (action) {
  | UpdateNewItem(itemName) =>
    Js.log("UpdateNewItem : " ++ itemName);
    let {newItem} = state;
    {
      ...state,
      newItem: {
        ...newItem,
        itemName,
      },
    };
  | DeleteItem(id) =>
    Js.log("DeleteItem : " ++ string_of_int(id));
    let {todolist, _} = state;
    {...state, todolist: List.filter(item => item.id != id, todolist)};
  | AddNewItem =>
    Js.log("AddNewItem");
    let {todolist, idCounter, newItem} = state;
    let newId = idCounter + 1;
    let newItem: todoListItem = {...newItem, id: newId, itemStatus: Open};
    {
      ...state,
      newItem: {
        ...initialNewItem,
        id: newId,
      },
      idCounter: newId,
      todolist: [newItem, ...todolist],
    };
  | CloseItem(id) =>
    Js.log("CloseItem : " ++ string_of_int(id));
    let {todolist} = state;
    let todolist =
      List.map(
        item => item.id == id ? {...item, itemStatus: Done("jetzt")} : item,
        todolist,
      );
    {...state, todolist};
  | OpenModal(_item) => {...state, modalVisible: true}
  | CloseModal => {...state, modalVisible: false}
  };
