import React, { Component, PropsWithChildren } from 'react';
import { SyntheticMouseEvent, SyntheticInputEvent, SyntheticChangeEvent } from '../lib/SyntheticEvents';

export interface TextInputProps {
  placeholder?: string
  maxlength?: number
  onChange?: (value: string) => void
  onInput?: (value: string) => void
}

type TextInputState = {
}

export class TextInput extends Component<PropsWithChildren<TextInputProps | any>, TextInputState> {
  constructor(props: PropsWithChildren<TextInputProps | any>) {
    super(props);
    console.log("construct TextInput (ts)");

    this._onChange = this._onChange.bind(this);
    this._onInput = this._onInput.bind(this);
    this._onMouseDown = this._onMouseDown.bind(this);

    this.state = {
    };
  }

  _onMouseDown(e: SyntheticMouseEvent) {
    console.log("TextInput.tsx _onMouseDown");
  }

  _onInput(e: SyntheticInputEvent) {
    this.props.onInput(e.value);
  }

  _onChange(e: SyntheticChangeEvent) {
    this.props.onChange(e.value);
  }

  render() {
    return React.createElement('TextInput', Object.assign({}, this.props, {
      onMouseDown: (e: SyntheticMouseEvent) => { this._onMouseDown(e) },
      onChange: (e: SyntheticChangeEvent) => { this._onChange(e) },
      onInput: (e: SyntheticInputEvent) => { this._onInput(e) }
    }), this.props.children);
  }
};